#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "gtkInjector.h"

extern void injectViews() {
	builder = gtk_builder_new();

	gtk_builder_connect_signals(builder, NULL);
	g_object_unref(builder);
}

