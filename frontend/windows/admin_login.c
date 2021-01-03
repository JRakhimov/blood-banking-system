#include <gtk/gtk.h>

GtkWidget *phone_number;
GtkWidget *password;

static void on_Login_button_clicked(void)
{
    const gchar *phone=gtk_entry_get_text(GTK_ENTRY(phone_number));
    const gchar *pass=gtk_entry_get_text(GTK_ENTRY(password));

    g_print("Username:%s\n", phone);
    g_print("Password:%s\n", pass);	

}
int main(int argc, char *argv[])
{
    GtkBuilder *builder; 
    GtkWidget *window;
    GtkWidget *button;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "project_ui.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "admin_login"));
    gtk_builder_connect_signals(builder, NULL);

    //g_object_unref(builder);
    
    phone_number=GTK_WIDGET(gtk_builder_get_object(builder, "admin_user"));
    password=GTK_WIDGET(gtk_builder_get_object(builder, "password1"));
    button=GTK_WIDGET(gtk_builder_get_object(builder,"Login_button1"));

    g_signal_connect(G_OBJECT(window), "destroy",
      G_CALLBACK(gtk_main_quit), NULL); 
    g_signal_connect(button, "clicked", G_CALLBACK(on_Login_button_clicked),NULL);
    gtk_widget_show(window);                
    gtk_main();
    return 0;
}

