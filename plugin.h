#ifndef PLUGIN_H
#define PLUGIN_H

typedef struct{
	const char *moduleName;
	int (*init)();
	int (*run)();
	void (*cleanup)();
} Plugin;

typedef Plugin* (*get_plugin_info_func)();

#endif
