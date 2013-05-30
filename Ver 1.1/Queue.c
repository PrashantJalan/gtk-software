#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int count=0;
char buf[5];
GtkWidget *b[11];
GtkWidget *label[11];
int length=0;
int x=20;
int flag=0; 							//For entering valid input
char msg1[20]="Length exceeded!";
char msg2[30]="Nothing to dequeue!";
char msg3[10]="No input!";
char msg4[40]="Input not of 'int' type!";

//Functions declaration
void quick_message (gpointer frame, char message[]);
void increase(GtkWidget *widget, gpointer entry);
void decrease(GtkWidget *widget, gpointer entry);
int key_released(GtkWidget *entry,  gpointer frame);
int queue_list(GtkWidget *widget, gpointer frame);
void restore(GtkWidget *widget, gpointer entry);
int  dequeue_list(GtkWidget *widget, gpointer frame);

/* Function to open a dialog box displaying the message provided. */

void quick_message (gpointer frame, char message[]) 
{

	GtkWidget *dialog, *label, *content_area;
   
	/* Create the widgets */
   	dialog = gtk_dialog_new_with_buttons ("Error",
					 frame,                                         
               				 GTK_DIALOG_DESTROY_WITH_PARENT,
                                         GTK_STOCK_OK,
                                         GTK_RESPONSE_NONE,
                                         NULL);
   	content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
   	label = gtk_label_new (message);
   	/* Ensure that the dialog box is destroyed when the user responds. */
   	g_signal_connect_swapped (dialog,
                             "response",
                             G_CALLBACK (gtk_widget_destroy),
                             dialog);
   	/* Add the label, and show everything we've added to the dialog. */
   	gtk_container_add (GTK_CONTAINER (content_area), label);
   	gtk_widget_show_all (dialog);
}

/*Func for label change on clicking + */
void increase(GtkWidget *widget, gpointer entry)
{
	count++;

  	sprintf(buf, "%d", count);
  	gtk_entry_set_text(entry, buf);
}

/*Func for label change when clicking - */
void decrease(GtkWidget *widget, gpointer entry)
{
  	count--;

  	sprintf(buf, "%d", count);
  	gtk_entry_set_text(entry, buf);
}

int key_released(GtkWidget *entry,  gpointer frame)
{
	int i;
	const char *temp;
	
	temp=gtk_entry_get_text(GTK_ENTRY(entry));
	strcpy(buf,temp);
	
	for(i=0;buf[i]!='\0';i++)
	{
		if (buf[i]<'0'|| buf[i]>'9')
		{
			flag=1;
			return 0;
		}
	}
	count=atoi(temp);
	return 0;
}

int queue_list(GtkWidget *widget, gpointer frame)
{
	if (flag==1)
	{
		quick_message(frame, msg4);
		flag=0;
		return 0;
	}
	if (buf[0]=='\0')
	{
		quick_message(frame,msg3);
		return 0;
	}
	if (length==11)
	{
		quick_message(frame,msg1);
		return 0;		
	}
	if (length>0)
	{
		label[length] = gtk_label_new ("<--");
		gtk_fixed_put(GTK_FIXED(frame), label[length], x-25, 60);
		gtk_widget_show(label[length]);
	}
	if (length>=0)
	{	
        b[length] = gtk_button_new_with_label(buf);
        gtk_widget_set_size_request(b[length], 40,40);
        gtk_fixed_put(GTK_FIXED(frame), b[length], x, 50);
	
	x=x+70;
	gtk_widget_show(b[length]);
	length++;
	}
	
	return 0;
}

void restore(GtkWidget *widget, gpointer entry)
{
		count=0;
		buf[0]='\0';
		gtk_entry_set_text(entry,"");
}

int  dequeue_list(GtkWidget *widget, gpointer frame)
{
	if (length>0 && length<12)
		gtk_widget_hide(label[length-1]);
	if(length==1)	
    {
		gtk_widget_hide(b[0]);
		length--;
		x=x-70;
		return 0;
	}
	else if(length>1)
	{ 
		gtk_widget_hide(b[0]);
		b[0]=b[1];
		x=20;
		int i;
		for(i=1;i<=length;i++)
		{
			gtk_fixed_put(GTK_FIXED(frame), b[i], x, 50);
			b[i]=b[i+1];
			x=x+70;
		}
		x=x-70;
		length--;
		return 0;
	}	
	else
	{
		quick_message(frame, msg2);
		return 0;
	}
}

int main (int argc, char *argv[])
{
	//Calling up the widgets
	GtkWidget *window;
	GtkWidget *frame;
	GtkWidget *plus;
	GtkWidget *minus;
	GtkWidget *entry;	//For entry of the integer
	GtkWidget *queue;
	GtkWidget *dequeue;
	
	gtk_init(&argc, &argv);	//Start of GTK

	/*Setting up the window*/

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 780, 400);
	gtk_window_set_title(GTK_WINDOW(window), "QUEUE");


	/*Setting up the frame*/

	frame = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window), frame);

	/*Setting up the entry field*/
	
	entry = gtk_entry_new ();
   	gtk_entry_set_max_length (GTK_ENTRY (entry), 3);
   	gtk_widget_set_size_request(entry, 70,30);
    gtk_fixed_put(GTK_FIXED(frame), entry, 195, 200);
	g_signal_connect(entry, "key-release-event", 
			G_CALLBACK(key_released), frame);
			
	/*Creating buttons*/

	plus = gtk_button_new_with_label("+");
	gtk_widget_set_size_request(plus, 80,35);
	gtk_fixed_put(GTK_FIXED(frame), plus, 75, 170);

	minus = gtk_button_new_with_label("-");
	gtk_widget_set_size_request(minus, 80, 35);
	gtk_fixed_put(GTK_FIXED(frame), minus, 75, 230);
	

	/*Queue and dequeue button*/

	queue = gtk_button_new_with_label("Queue");
	gtk_widget_set_size_request(queue, 90,45);
	gtk_fixed_put(GTK_FIXED(frame), queue, 125, 290);
        
	dequeue = gtk_button_new_with_label("Dequeue");
    gtk_widget_set_size_request(dequeue, 90,45);
    gtk_fixed_put(GTK_FIXED(frame), dequeue, 310, 290);


	//Show command
	gtk_widget_show_all(window);

	/*destroy signal*/
	g_signal_connect(window, "destroy",
		G_CALLBACK(gtk_main_quit), NULL);

	/*If Button is clicked*/
	g_signal_connect(plus, "clicked", 
      		G_CALLBACK(increase), entry);

	g_signal_connect(minus, "clicked", 
      		G_CALLBACK(decrease), entry);

   	g_signal_connect (entry, "activate",
		      G_CALLBACK (queue_list),frame);

   	g_signal_connect (entry, "activate",
		      G_CALLBACK (restore), entry);
        
	g_signal_connect(queue, "clicked",
        	G_CALLBACK(queue_list), frame);
	
	g_signal_connect(queue, "clicked",
			G_CALLBACK(restore), entry);
			
	g_signal_connect(dequeue, "clicked",
		G_CALLBACK(dequeue_list), frame);

	gtk_main();	//End of GTK function

	return 0;
}

