#include "view_injector.h"
#include "core/socket.h"

int main(int argc, char *argv[]) {
	// initSocket(); // initialize socket connection
	gtk_init(&argc, &argv);
	
	injectViews();
	
	if(strlen(userEmailData) != 0)
		gtk_widget_show(home_window);
	else
		gtk_widget_show(main_window);
	gtk_main();
	return 0;
}

