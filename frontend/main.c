#include "windowsInjector.h"
#include "socket/socketClient.h"

int main(int argc, char *argv[]) {
	setbuf(stdout, NULL);

	initSocket();
	gtk_init(&argc, &argv);
	
	injectViews();

	gtk_widget_show(userWindow);
	
	gtk_main();
	
	return 0;
}

