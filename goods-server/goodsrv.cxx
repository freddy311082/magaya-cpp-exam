//-< GOODSRV.CXX >---------------------------------------------------*--------*
// GOODS                     Version 1.0         (c) 1997  GARRET    *     ?  *
// (Generic Object Oriented Database System)                         *   /\|  *
//                                                                   *  /  \  *
//                          Created:      7-Jun-97    K.A. Knizhnik  * / [] \ *
//                          Last update: 17-Oct-97    K.A. Knizhnik  * GARRET *
//-------------------------------------------------------------------*--------*
// Example of server program
//-------------------------------------------------------------------*--------*

#include "server.h"

#define GOODSRV_CFG_FILE_NAME  "goodsrv.cfg"

#define Kb 1024

unsigned init_map_file_size = 8*1024;/*Kb*/
unsigned init_index_file_size = 4*1024;/*Kb*/
// amount of memory after which allocation GC is initiated
unsigned gc_init_timeout = 60; /*sec*/
unsigned gc_init_allocated = 1024; /*Kb*/
unsigned gc_init_idle_period = 0; /*sec (0 - disabled)*/
unsigned gc_init_min_allocated = 0; /*Kb*/
unsigned gc_response_timeout = 24*60*60; /*sec*/
unsigned gc_grey_set_threshold=1024; /* grey references */
unsigned max_data_file_size = 0; /*Kb, 0 - not limited*/
unsigned max_objects = 0; /* 0 - not limites */

unsigned sync_log_writes = True;
unsigned permanent_backup = False;
unsigned trans_preallocated_log_size = 0;/*Kb*/
unsigned trans_max_log_size = 8*1024;/*Kb*/
unsigned trans_wait_timeout = 600; /*sec*/
unsigned trans_retry_timeout = 5; /*sec*/
unsigned checkpoint_period = 0; /*sec (0-disabled) */
unsigned dynamic_reclustering_limit = 0; /*disabled*/

unsigned lock_timeout = 600;

unsigned page_pool_size = 4096;
 
unsigned cluster_size = 512;

char* index_file_name;
char* map_file_name;
char* data_file_name;
char* trans_file_name;
char* history_file_name;

struct param_binding {
     char const* param_name;
     unsigned*   param_ivalue;
     char const* param_meaning;	
     boolean     (*set_param)(dbs_server* srv, unsigned val);
     char**      param_svalue;
};

boolean set_max_data_file_size(dbs_server* srv, unsigned val)
{
    srv->mem_mgr->set_file_size_limit(fsize_t(val)*Kb);
    return True;	
}

boolean set_max_objects(dbs_server* srv, unsigned val)
{
    srv->mem_mgr->set_objects_limit(val);
    return True;	
}

boolean set_gc_init_timeout(dbs_server* srv, unsigned val)
{
    srv->mem_mgr->set_gc_init_timeout(time_t(val));
    return True;	
}

boolean set_gc_grey_set_threshold(dbs_server* srv, unsigned val)
{
    srv->mem_mgr->set_gc_grey_set_extension_threshold(val);
    return True;	
}

boolean set_gc_response_timeout(dbs_server* srv, unsigned val)
{
    srv->mem_mgr->set_gc_response_timeout(time_t(val));
    return True;	
}

boolean set_gc_init_allocated(dbs_server* srv, unsigned val)
{
    srv->mem_mgr->set_gc_init_alloc_size(val*Kb);
    return True;	
}

boolean set_gc_init_idle_period(dbs_server* srv, unsigned val)
{
    srv->mem_mgr->set_gc_init_idle_period(time_t(val));
    return True;	
}

boolean set_gc_init_min_allocated(dbs_server* srv, unsigned val)
{
    srv->mem_mgr->set_gc_init_min_allocated(val*Kb);
    return True;	
}

boolean set_permanent_backup(dbs_server* srv, unsigned val)
{
    srv->trans_mgr->set_backup_type(val ? server_transaction_manager::bck_permanent
					: server_transaction_manager::bck_snapshot);
    return True;
}


boolean set_checkpoint_period(dbs_server* srv, unsigned val)
{
    srv->trans_mgr->set_checkpoint_period(val);
    return True;
}

boolean set_max_log_size(dbs_server* srv, unsigned val)
{
    srv->trans_mgr->set_log_size_limit(fsize_t(val)*Kb);	
    return True;
}

boolean set_preallocated_log_size(dbs_server* srv, unsigned val)
{
    srv->trans_mgr->set_preallocated_log_size(fsize_t(val)*Kb);	
    return True;
}

boolean set_wait_timeout(dbs_server* srv, unsigned val)
{
    srv->trans_mgr->set_global_transaction_commit_timeout(val);
    return True;
}

boolean set_retry_timeout(dbs_server* srv, unsigned val)
{
    srv->trans_mgr->set_global_transaction_get_status_timeout(val);
    return True;
}

boolean set_dynamic_reclustering_limit(dbs_server* srv, unsigned val)
{
    srv->trans_mgr->set_dynamic_reclustering_limit(val);
    return True;
}

boolean set_lock_timeout(dbs_server* srv, unsigned val)
{
    srv->obj_mgr->set_lock_timeout(val);
    return True;
}

boolean set_cluster_size(dbs_server* srv, unsigned val)
{
    srv->set_object_cluster_size_limit(val);
    return True;
}

param_binding goodsrv_params[] = { 
{"memmgr.init_map_file_size", &init_map_file_size,
 "initial size for memory map file"},
{"memmgr.init_index_file_size", &init_index_file_size,
 "initial size for object index file"},
{"memmgr.gc_init_timeout", &gc_init_timeout,
 "timeout for GC initiation", set_gc_init_timeout},
{"memmgr.gc_response_timeout", &gc_response_timeout,
 "timeout for waiting GC coordinator response", set_gc_response_timeout},
{"memmgr.gc_init_allocated", &gc_init_allocated,
 "size of allocated memory after which GC is started", set_gc_init_allocated},
{"memmgr.gc_init_idle_period", &gc_init_idle_period,
 "idle period after which GC is initated", set_gc_init_idle_period},
{"memmgr.gc_init_min_allocated", &gc_init_min_allocated,
 "minimal allocated memory to initiate GC", set_gc_init_min_allocated},
{"memmgr.gc_grey_set_threshold", &gc_grey_set_threshold,
 "grey references set extension threshold", set_gc_grey_set_threshold},
{"memmgr.max_data_file_size", &max_data_file_size,
 "limitation for size of storage data file", set_max_data_file_size},
{"memmgr.max_objects", &max_objects,
 "limitation for number of objects in storage", set_max_objects},
{"memmgr.index_file_name", NULL,
 "name of object index file", NULL, &index_file_name},
{"memmgr.map_file_name", NULL,
 "name of memory mapping file", NULL, &map_file_name},

{"transmgr.sync_log_writes", &sync_log_writes,
 "synchronous transaction log write mode"},
{"transmgr.permanent_backup", &permanent_backup, 
 "permanent backup type (snapshot backup if 0)", set_permanent_backup},
{"transmgr.max_log_size", &trans_max_log_size, 
 "limitation for transaction log size", set_max_log_size},
{"transmgr.preallocated_log_size", &trans_preallocated_log_size, 
 "initial size of transaction log file", set_preallocated_log_size},
{"transmgr.checkpoint_period", &checkpoint_period, 
 "checkpoint initation period", set_checkpoint_period},
{"transmgr.wait_timeout", &trans_wait_timeout, 
 "timeout for committing global transaction", set_wait_timeout},
{"transmgr.retry_timeout", &trans_retry_timeout, 
 "timeout for requesting status of global transaction", set_retry_timeout},
{"transmgr.dynamic_reclustering_limit", &dynamic_reclustering_limit, 
 "maximal size of object to be reclustered", set_dynamic_reclustering_limit},
{"transmgr.log_file_name", NULL,
 "name of transaction log file", NULL, &trans_file_name},
{"transmgr.history_file_name", NULL,
 "name of global transaction history file", NULL, &history_file_name},

{"objmgr.lock_timeout", &lock_timeout, 
 "timeout for waiting lock granting", set_lock_timeout},

{"poolmgr.page_pool_size", &page_pool_size,
 "size of server page pool"},
{"poolmgr.data_file_name", NULL,
 "name of storage data file", NULL, &data_file_name},

{"server.cluster_size", &cluster_size, 
  "limitation for object cluster size", set_cluster_size},
{NULL}
};

union option_value { 
    unsigned ivalue;
    char*    svalue;
};

boolean parse_option(char* buf, param_binding* &param, option_value& u)
{
    char* np = buf;
    while (*np == ' ' || *np == '\t') np += 1;
    char* p = np;
    if (*p != '#' && *p != '\n') { 
	while (*p != '\0' && *p != ' ' && *p != '\t' && *p != '=')p++;
	if (*p == '\0') { 
	    return False;
        }
	char* enp = p;
	if (*p++ != '=') { 
	    while (*p != '=' && *p != '\0') p += 1;
	    if (*p++ != '=') { 
		return False;
            }
        }  
	char c = *enp;
	*enp = '\0';
 	for (param_binding* pb = goodsrv_params;
	     pb->param_name != NULL;
             pb++)
        {
             if (stricmp(pb->param_name, np) == 0) 
             { 
		 *enp = c;
	         param = pb;
		 if (pb->param_ivalue != NULL) { 
		     if (sscanf(p, "%i", &u.ivalue) != 1) { 
			 return False;
		     }
		 } else { 
		     internal_assert(pb->param_svalue != NULL);
		     while (*p != '"') { 
			 if (*p == '\0') { 
			     return False;
			 }
			 p += 1;
		     }
		     char* name = ++p;
		     while (*p != '"') { 
			 if (*p == '\0') { 
			     return False;
			 }
			 p += 1;
		     }
		     int len = p - name;
		     u.svalue = new char[len+1];
		     memcpy(u.svalue, name, len);
		     u.svalue[len] = '\0';		     
		 }
		 return True;
             }
        }
	*enp = c;
	return False;
    }
    param = NULL;
    return True;
}

void read_goodsrv_configuration(const char* cfg_file_name)
{
    FILE* cfg = fopen(cfg_file_name, "r");
    if (cfg != NULL) { 
	char buf[MAX_CFG_FILE_LINE_SIZE];

	while (fgets(buf, sizeof buf, cfg) != NULL) { 
	    option_value u;
	    param_binding* pb;
	    if (parse_option(buf, pb, u)) { 
		if (pb != NULL) {  
		    if (pb->param_ivalue != NULL) {
			*pb->param_ivalue = u.ivalue;
		    } else { 
			if (*pb->param_svalue != NULL) { 
			    delete[] *pb->param_svalue;
			}
			*pb->param_svalue = u.svalue;
		    }			
                }
            } else { 
		console::output("Incorrect string in %s configuration file: %s"
				,cfg_file_name, buf);
            } 	
	}
        fclose(cfg);
    }
}

#define SHOW_ALL "servers clients memory transaction classes"

void on_backup_completion(dbs_server&, file& backup_file, boolean result)
{
    console::message(msg_notify|msg_time, 
		     "Backup to file \"%s\" %s finishished\n",
		     backup_file.get_name(), 
		     result ? "successfully" : "abnormally"); 
} 

struct trace_option { 
    const char* option;
    int         mask;
    const char* meaning;
};

static trace_option trace_options_table[] = { 
    {"error",     msg_error, "messages about some non-fatal errors"},
    {"notify",    msg_notify, "notification messages"}, 
    {"login",     msg_login,   "messages about clients login/logout"},
    {"warning",   msg_warning, "messages about some incorrect operations"},
    {"important", msg_important, "messages about some important events"},
    {"object",    msg_object,"messages about operation with object instances"},
    {"locking",   msg_locking, "object lock related tracing"},
    {"request",   msg_request, "trace requests received by server"},
    {"gc",        msg_gc, "trace garbage collector activity"},
    {"all",       msg_all, "output all messages"},
    {"none",      msg_none, "ignore all messages"},
    {NULL}
};
    

const int max_cmd_len = 256;
static char log_file_name[max_cmd_len];

static char monitor_options[max_cmd_len];
static time_t monitor_period;
static semaphore monitor_sem;
static event monitor_term_event;

void task_proc monitor(void* arg)
{
    dbs_server* dbs = (dbs_server*)arg;
    while (monitor_period != 0) { 
	if (!monitor_sem.wait_with_timeout(monitor_period)) { 
	    console::output("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	    console::message(msg_output|msg_time, "Monitoring: %s\n", 
			     monitor_options);
	    dbs->dump(monitor_options);
	}
    }
    monitor_term_event.signal();
}


boolean arg2int(char* arg, int& val) 
{
    char c;
    return sscanf(arg, "%i %c", &val, &c) == 1; 
}

void administrator_dialogue(char* database_config_name, dbs_server& server)
{ 
    char buf[max_cmd_len];
    os_file* backup_file = NULL;
    int number_of_errors = 0;

    console::message(msg_notify, server.open(database_config_name)
		     ? "GOODS server started...\n"
		     : "Failed to start server\n");
    
    while(True) { 
	char  cmd[max_cmd_len];
 	char  arg[3][max_cmd_len];
	int   arg_offs[2];
	int   n_args;

	console::output(">");
	if (!console::input(buf, sizeof buf)) { 
	    break;
	}
	n_args = sscanf(buf, "%s%n%s%n%s%s", cmd, 
			&arg_offs[0], arg[0], &arg_offs[1], arg[1], arg[2]);
	if (n_args <= 0) { 
	    continue;
	}
	if (stricmp(cmd, "open") == 0) { 
	    if (server.opened) { 
		console::output("Server is already opened\n");
	    } else { 
		console::message(msg_notify, server.open(database_config_name)
				 ? "GOODS server started...\n"
				 : "Failed to start server\n");
	    }
	} else if (stricmp(cmd, "close") == 0) { 
	    server.close();
	} else if (stricmp(cmd, "exit") == 0) { 
  	    break;
	} else if (stricmp(cmd, "show") == 0) { 
	    if (strstr(buf+arg_offs[0], "setting") != NULL) {
		for (param_binding* pb = goodsrv_params;
		     pb->param_name != NULL;
		     pb++)
		{
		    if (pb->param_ivalue != NULL) { 
			console::output("%s = %u\n", 
					pb->param_name, *pb->param_ivalue);
		    } else { 
			console::output("%s = \"%s\"\n", 
					pb->param_name, *pb->param_svalue);
		    }
		}
	    } 
	    if (server.opened) { 
		server.dump(n_args == 1 ? SHOW_ALL : buf + arg_offs[0]); 
	    } else { 
		console::output("Server is not opened\n");
	    }
	} else if (stricmp(cmd, "monitor") == 0) { 
	    int period;
	    if (n_args < 2 || !arg2int(arg[0], period)) { 
		console::output("Monitoring period is not specified\n");
	    } else { 
		if (n_args > 2) { 
		    strcpy(monitor_options, buf+arg_offs[1]);
		} else { 
		    strcpy(monitor_options, SHOW_ALL);
		}
		if (monitor_period == 0) { 
		    if (period != 0) {
			monitor_period = period;
			monitor_term_event.reset();
			task::create(monitor, &server);
		    } 
		} else { 
		    monitor_period = period;
		    monitor_sem.signal();
		    if (monitor_period == 0) {
			monitor_term_event.wait();
		    }
		}
	    }
	} else if (strincmp(cmd, "backup", 6) == 0) { 
	    if (!server.opened) { 
		console::output("Server is not opened\n");
	    } else if (server.backup_started) { 
		console::output("Backup is already started\n");
	    } else { 
                if (n_args >= 2) { 
		    int timeout = 0, log_size = 0;
		    if (n_args >= 3 && !arg2int(arg[1], timeout)) { 
			console::output("Backup timeout value is not valid "
					"integer constant: '%s'\n", arg[1]);
			continue;
		    }			
		    if (n_args >= 4 && !arg2int(arg[2], log_size)) { 
			console::output("Backup log size threshold value is "
					"not valid integer constant: '%s'\n", 
					arg[2]);
			continue;
		    }			
		    delete backup_file;
		    backup_file = new os_file(arg[0]);
		    server.start_backup(*backup_file, timeout, 
					fsize_t(log_size)*Kb,
					on_backup_completion);
		} else { 
		    console::output("Name of backup file is not specified\n");
		}	
	    }	
	} else if (stricmp(cmd, "stop") == 0) { 
	    if (!server.backup_started) {
		console::output("No backup process is active\n");
	    } else { 
		server.stop_backup();
	    }
	} else if (stricmp(cmd, "restore") == 0) {  
	    if (server.opened) { 
		console::output("Restore is possible only for closed"
				 " server\n");
	    } else { 
		if (n_args == 2) { 
		    backup_file = new os_file(arg[0]);
		    server.restore(*backup_file, database_config_name);
		    delete backup_file;
		    backup_file = NULL;
		} else { 
		    console::output("Name of backup file is not specified\n");
		}	
	    }
	} else if (stricmp(cmd, "log") == 0) {
	    if (n_args >= 2)
	    {
		*log_file_name = '\0';
		if (strcmp(arg[0], "-") == 0) { 
		    console::use_log_file(NULL);
		} else { 
		    FILE* f = fopen(arg[0], "w");
		    if (f == NULL) { 
			console::output("Failed to open log file '%s'\n",
					arg[0]);
		    } else { 
			strcpy(log_file_name, arg[0]);
		    }
		    console::use_log_file(f);
		}
	    } else { 
		if (*log_file_name) { 
		    console::output("Write output to log file '%s'\n", 
				     log_file_name);
		} else { 
		    console::output("No log file is used\n");
		}
	    }
	} else if (stricmp(cmd, "trace") == 0) {
	    int n_options = 0;
	    int mask = 0;
	    char* opt = buf + arg_offs[0];

	    while (sscanf(opt, "%s%n", arg[0], arg_offs) == 1) { 
		trace_option* tp = trace_options_table;
		while (tp->option != NULL) { 
		    if (stricmp(arg[0], tp->option) == 0) { 
			mask |= tp->mask;
			break;
		    }
		    tp += 1;
		}
		if (tp->option == NULL) { 
		    console::output("Unknown trace option: '%s'\n", arg[0]);
		    break;
		}
		n_options += 1;
		opt += *arg_offs;
	    }
	    if (n_options == 0) { 
		if (console::trace_mask == 0) { 
		    console::output("All trace messages are ignored\n");
		} else { 
		    trace_option* tp = trace_options_table;
		    console::output("Trace following messages:");
		    while (tp->option != NULL) { 
			if ((tp->mask & console::trace_mask)
			    && tp->mask != msg_all)
			{
			    console::output(" %s", tp->option);
			}
			tp += 1;
		    }
		    console::output("\n");
		}
	    } else { 
		console::trace_mask = mask;
	    }
	} else if (stricmp(cmd, "set") == 0) {
	    param_binding* pb;
	    option_value u;
	    if (parse_option(buf+arg_offs[0], pb, u) && pb != NULL) { 
                if (pb->set_param != NULL) { 
		   if (!(*pb->set_param)(&server, u.ivalue)) { 
		       console::output("Invalid value of paramater: %u\n",
				       u.ivalue);
                   } else { 
		       *pb->param_ivalue = u.ivalue;
		   }
		} else {
		   console::output("This parameter should be set "
				   "in configuration file\n");
                }
            } else { 
		console::output("Invalid set instruction: %s\n", 
				buf+arg_offs[0]);
            } 			
	} else { 
	    boolean help = stricmp(cmd, "help") == 0; 
	    if (help || ++number_of_errors > 1) { 
		number_of_errors = 0;
		if (help && n_args >= 2) { 
		    if (stricmp(arg[0], "trace") == 0) {
			console::output("\
Syntax: trace [TRACE_MESSAGE_CLASS]\n\
Description: Select classes of output messages:\n");
			for (trace_option* tp = trace_options_table;
			     tp->option != NULL;
			     tp++)
			{
			    console::output(" %s - %s\n", 
					    tp->option, tp->meaning);
			}
			continue;
		    }
		    if (stricmp(arg[0], "set") == 0) {
			console::output("\
Syntax: set PARAMETER = INTEGER_VALUE\n\
Description: Set one of the following parameters:\n");
		        for (param_binding* pb = goodsrv_params; 
			     pb->param_name != NULL;	
			     pb++)
			{ 
			    if (pb->set_param != NULL) { 
				console::output(" %s - %s\n", 
						pb->param_name, 
						pb->param_meaning);
			    }
			}
			continue;
		    }
		    if (stricmp(arg[0], "show") == 0) {
			console::output("\
Syntax: show [settings %s]\n\
Description: Show information about storage server current state.\n\
  By default all categories are shown.\n", SHOW_ALL);
			continue;
		    } 
		    if (stricmp(arg[0], "monitor") == 0) {
			console::output("\
Syntax: monitor PERIOD [%s]\n\
Description: Perform periodical monitoring of storage server state.\n\
  By default all categories are shown.\n", SHOW_ALL);
			continue;
		    } 
		} 
		console::output("\
Commands:\n\
  help [COMMAND]                        print information about command(s)\n\
  open					open database\n\
  close					close database\n\
  exit					terminate server\n\
  show [CATEGORIES]                     show current server state\n\
  monitor PERIOD [CATEGORIES]           periodical monitoring of server state\n\
  backup FILE_NAME [TIME [LOG_SIZE]]	schedule online backup process\n\
  stop backup				stop backup process\n\
  restore BACKUP_FILE_NAME		restore database from the backup\n\
  trace [TRACE_MESSAGE_CLASS]           select classes of output messages\n\
  log [LOG_FILE_NAME|\"-\"]               set log file name\n\
  set PARAMETER = INTEGER_VALUE		set server parameters\n");
	    } else { 
		console::output("Unknown command: %s\n", cmd);
		continue;
	    }
	}
	number_of_errors = 0;
    }
    if (server.opened) { 
	server.close();
    }
    if (monitor_period != 0) {
	monitor_period = 0;
	monitor_sem.signal();
	monitor_term_event.wait();
    }
    delete backup_file;
    console::message(msg_notify, "GOODS server is terminated\n");
}

int main(int argc, char* argv[]) 
{
    int id = 0;
    task::initialize();
    if (argc < 2 || argc > 4) { 
	console::error("GOODS storage server.\n"
	    	       "Usage: goodsrv <storage name> [<storage-id> [<trace-file-name>]]\n");
    }
    if (argc >= 3) { 
	if (sscanf(argv[2], "%d", &id) != 1) { 
	    console::error("Bad storage identifier: '%s'\n", argv[2]);
	}
    }
    if (argc == 4 && strcmp(argv[3], "-") != 0) { 
	FILE* f = fopen(argv[3], "w");
	if (f == NULL) { 
	    console::output("Failed to open log file '%s'\n", argv[3]);
	} else { 
	    strncpy(log_file_name, argv[3], sizeof log_file_name);
	    console::use_log_file(f);
	}
    }
    char* name = argv[1];
    char id_str[8];
    int len = strlen(name) + 5;
    *id_str = '\0';
    if (id != 0) { 
	len += sprintf(id_str, "%d", id);
    }

    char* cfg_name = new char[len];
    char* srv_name = new char[len];
    data_file_name = new char[len];
    trans_file_name = new char[len];
    history_file_name = new char[len];
    index_file_name = new char[len];
    map_file_name = new char[len];

    sprintf(cfg_name, "%s.cfg", name);        
    sprintf(srv_name, "%s%s.srv", name, id_str);
    sprintf(data_file_name, "%s%s.odb", name, id_str);
    sprintf(trans_file_name, "%s%s.log", name, id_str);
    sprintf(history_file_name, "%s%s.his", name, id_str);
    sprintf(map_file_name, "%s%s.map", name, id_str);
    sprintf(index_file_name, "%s%s.idx", name, id_str);

    read_goodsrv_configuration(GOODSRV_CFG_FILE_NAME);
    read_goodsrv_configuration(srv_name);

    os_file   odb_file(data_file_name);
    os_file   log_file(trans_file_name);
    os_file   his_file(history_file_name);
    mmap_file idx_file(index_file_name, init_index_file_size*Kb);
    mmap_file map_file(map_file_name, init_map_file_size*Kb);

    object_manager    obj_mgr((time_t)lock_timeout);
    page_pool_manager pool_mgr(odb_file, page_pool_size);
    dbs_class_manager class_mgr;
    gc_memory_manager mem_mgr(idx_file, map_file, 
			      gc_init_timeout, 
			      gc_init_allocated*Kb,
			      time_t(gc_init_idle_period), 
			      gc_init_min_allocated*Kb, 
			      gc_grey_set_threshold, 
			      fsize_t(max_data_file_size)*Kb, 
			      max_objects,
			      gc_response_timeout);

    log_transaction_manager trans_mgr(log_file, his_file, NULL, sync_log_writes,
				      (server_transaction_manager::backup_type)
  				       permanent_backup, 
				      fsize_t(trans_max_log_size)*Kb,
				      fsize_t(trans_preallocated_log_size)*Kb,
				      time_t(checkpoint_period), 
				      time_t(trans_wait_timeout), 
				      time_t(trans_retry_timeout),
				      dynamic_reclustering_limit);

    storage_server server(id, 
			  obj_mgr, 
			  pool_mgr, 
			  class_mgr, 
			  mem_mgr, 
			  trans_mgr);
 
    administrator_dialogue(cfg_name, server);

    return EXIT_SUCCESS;
}

