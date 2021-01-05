#include "../gtkInjector.h"

#include <gtk/gtkx.h>

typedef enum{
  ID,
  BLOODTYPE,
  ACTION,
  STATUS,
  NUM_COLUMNS
} Column_type;

GtkBox *userBox;
GtkStack *userStack;
GtkLabel *label1;
GtkButton button1;
GtkButton button2;
GtkButton button3;
GtkButton button4;
GtkStackSwitcher *switcher;
GtkWidget *grid1;
GtkWidget *grid2;
GtkWidget *grid3;
GtkTreeView *tree;
GtkTreeModel *model;

static GtkTreeModel *create_and_fill_model (void){
GtkListStore *store;
GtkTreeIter iter;

store=gtk_list_store_new (4,G_TYPE_STRING, G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);

gtk_list_store_append(store,&iter);
gtk_list_store_set (store, &iter,
		ID, "1",
		BLOODTYPE, "A+",
		ACTION,"Get",
		STATUS, "Accepted",
		-1);

return GTK_TREE_MODEL (store);
}

void initUserWindow() {
	userWindow = GTK_WIDGET(gtk_builder_get_object(builder, "user_page"));

  tree=GTK_WIDGET(gtk_builder_get_object(builder,"TreeView"));

	grid1 = GTK_WIDGET(gtk_builder_get_object(builder, "get_switch"));
	grid2 = GTK_WIDGET(gtk_builder_get_object(builder, "donate_switch"));
	grid3 = GTK_WIDGET(gtk_builder_get_object(builder, "history_switch"));

  userBox = GTK_BOX(gtk_builder_get_object(builder, "user_box"));
  userStack = GTK_STACK(gtk_builder_get_object(builder, "pages"));
  switcher = GTK_STACK_SWITCHER(gtk_builder_get_object(builder, "switch"));

  GtkTreeViewColumn *column1=gtk_tree_view_column_new_with_attributes("ID",gtk_cell_renderer_text_new (),"text",ID,NULL);
	GtkTreeViewColumn *column2=gtk_tree_view_column_new_with_attributes("Blood Type",gtk_cell_renderer_text_new (),"text",BLOODTYPE,NULL);  
	GtkTreeViewColumn *column3=gtk_tree_view_column_new_with_attributes("Action",gtk_cell_renderer_text_new (),"text",ACTION,NULL);
	GtkTreeViewColumn *column4=gtk_tree_view_column_new_with_attributes("Status",gtk_cell_renderer_text_new (),"text",STATUS,NULL);

	gtk_tree_view_column_set_expand(column1,TRUE);
	gtk_tree_view_column_set_expand(column2,TRUE);
	gtk_tree_view_column_set_expand(column3,TRUE);
	gtk_tree_view_column_set_expand(column4,TRUE);

	gtk_tree_view_append_column (GTK_TREE_VIEW (tree), column1);
	gtk_tree_view_append_column (GTK_TREE_VIEW (tree), column2);
	gtk_tree_view_append_column (GTK_TREE_VIEW (tree), column3);
	gtk_tree_view_append_column (GTK_TREE_VIEW (tree), column4);

	model=create_and_fill_model();
	gtk_tree_view_set_model (GTK_TREE_VIEW (tree), model);
}