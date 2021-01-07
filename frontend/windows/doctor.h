#include "../gtkInjector.h"

#include <gtk/gtk.h>

typedef enum {
  D_T_ID,
  D_T_NAME,
  D_T_BLOODTYPE,
  D_T_DONATIONDATE,
  D_T_ACTION,
  D_T_NUM_COLUMNS
} Doctor_Column_type;


GtkTreeView *treead;
GtkTreeModel *modelad;
GtkWidget *insert_button;
GtkWidget *delete_button;
GtkWidget *modify_button;
GtkWidget *logout_button;
GtkTreeSelection *selection;

static GtkTreeModel *create_and_fill_doctor_model (struct Record *records) {
  GtkListStore *store;
  GtkTreeIter iter;

  store = gtk_list_store_new(5, G_TYPE_INT,G_TYPE_INT,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);

  gtk_list_store_append(store,&iter);
  gtk_list_store_set (
    store,
    &iter,
    D_T_ID, records[0].id,
    D_T_NAME, records[0].donor_id,
    D_T_BLOODTYPE, records[0].bloodType,
    D_T_DONATIONDATE, records[0].date,
    D_T_ACTION, records[0].status,
    -1
  );

  gtk_list_store_append(store,&iter);
  gtk_list_store_set (
    store,
    &iter,
    D_T_ID, records[1].id,
    D_T_NAME, records[1].donor_id,
    D_T_BLOODTYPE, records[1].bloodType,
    D_T_DONATIONDATE, records[1].date,
    D_T_ACTION, records[1].status,
    -1
  );

  printf("1) %ld\n", sizeof(*records));
  printf("2) %ld\n", sizeof(struct Record));

  for (int i = 0; i < sizeof(records) / sizeof(struct Record); i++) {
    gtk_list_store_append(store,&iter);
    gtk_list_store_set (
      store,
      &iter, D_T_ID,
      records[i].id + '0',
      D_T_NAME,
      records[i].donor_id + '0',
      D_T_BLOODTYPE,
      records[i].bloodType,
      D_T_DONATIONDATE,
      records[i].date,
      D_T_ACTION,
      records[i].status,
      -1
    );
  }

  return GTK_TREE_MODEL(store);
}

void on_doctor_page_show() {
  struct Request request;
  struct Response response;

  sprintf(request.route.module, RECORD_MODULE);
  sprintf(request.route.method, GET_PENDING_DONATES_METHOD);

  sendAll(socketClientId, &request, sizeof(request), 0);
  recv(socketClientId, &response, sizeof(response), MSG_WAITALL);

  printf("[DOCTOR] Status: %d\n", response.status);
  printf("[DOCTOR] Record: %d\n", response.data.records[0].id);

  if (response.status == 1) {
    modelad = create_and_fill_doctor_model(response.data.records);
    gtk_tree_view_set_model(GTK_TREE_VIEW (treead), modelad);
  }
}

static void onAdminLoginClicked(void) {
	gtk_widget_hide(doctorWindow);
  gtk_widget_show(initialWindow);
}

static void onTreeViewRowActivated(GtkTreeView *tree, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data){
  gtk_widget_show(editRecordWindow);
}

void initDoctorWindow() {
  doctorWindow = GTK_WIDGET(gtk_builder_get_object(builder, "doctor_page"));
  editRecordWindow = GTK_WIDGET(gtk_builder_get_object(builder, "edit_window"));

  treead = GTK_TREE_VIEW(gtk_builder_get_object(builder,"treeview1"));

	insert_button=GTK_WIDGET(gtk_builder_get_object(builder,"insert_doctor_button"));
	delete_button=GTK_WIDGET(gtk_builder_get_object(builder,"delete_doctor_button"));
	
	logout_button=GTK_WIDGET(gtk_builder_get_object(builder,"doctor_logout"));

  GtkTreeViewColumn *column1=gtk_tree_view_column_new_with_attributes("ID",gtk_cell_renderer_text_new (),"text",D_T_ID,NULL);  
  GtkTreeViewColumn *column2=gtk_tree_view_column_new_with_attributes("Name",gtk_cell_renderer_text_new (),"text",D_T_NAME,NULL);  
	GtkTreeViewColumn *column3=gtk_tree_view_column_new_with_attributes("Blood Type",gtk_cell_renderer_text_new (),"text",D_T_BLOODTYPE,NULL);
	GtkTreeViewColumn *column4=gtk_tree_view_column_new_with_attributes("Donation date",gtk_cell_renderer_text_new (),"text",D_T_DONATIONDATE,NULL);
	GtkTreeViewColumn *column5=gtk_tree_view_column_new_with_attributes("Action",gtk_cell_renderer_text_new (),"text",D_T_ACTION,NULL);

	gtk_tree_view_column_set_expand(column1,TRUE);
	gtk_tree_view_column_set_expand(column2,TRUE);
	gtk_tree_view_column_set_expand(column3,TRUE);
	gtk_tree_view_column_set_expand(column4,TRUE);
	gtk_tree_view_column_set_expand(column5,TRUE);

	gtk_tree_view_append_column (GTK_TREE_VIEW (treead), column1);
	gtk_tree_view_append_column (GTK_TREE_VIEW (treead), column2);
	gtk_tree_view_append_column (GTK_TREE_VIEW (treead), column3);
	gtk_tree_view_append_column (GTK_TREE_VIEW (treead), column4);
	gtk_tree_view_append_column (GTK_TREE_VIEW (treead), column5);

	g_signal_connect(logout_button, "clicked", G_CALLBACK(onAdminLoginClicked),NULL);
	// g_signal_connect(delete_button, "clicked", G_CALLBACK(delete_clicked),NULL);

	g_signal_connect(treead, "row-activated",(GCallback) onTreeViewRowActivated, NULL);

}
