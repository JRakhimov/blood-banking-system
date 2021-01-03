#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>

#include "gtkInjector.h"
#include "./windows/initial.h"

extern void injectViews() {
	builder = gtk_builder_new();

	gtk_builder_add_from_file(builder, "./glade/project_ui.glade", NULL);

	initInitialWindow();

	gtk_builder_connect_signals(builder, NULL);
	g_object_unref(builder);
}

