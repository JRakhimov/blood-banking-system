#include "windowsInjector.h"

int main(int argc, char *argv[]) {
	// initSocket(); // initialize socket connection
	gtk_init(&argc, &argv);
	
	injectViews();

	gtk_widget_show(initialWindow);
	
	gtk_main();
	
	return 0;
}

