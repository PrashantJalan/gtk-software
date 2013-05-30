#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <math.h>

#define WIDTH 40
#define HEIGHT 40
#define LIMIT 20

int count=0;
char buf[5]="0";
int size=0;
char size_c[5]="0";
int depth=0;
int depth_max=0;	//For displaying
char depth_c[5]="0";
int depth_record[200];		//So that we can find the max. depth
int y=25;
int i=1;	//For use in the position_button func

typedef struct node node;

struct node
{
	int x;	//For determining the x co-ordinate of button
	int data;
	GtkWidget* b;	//For the button
	GtkWidget *label_vertical[3];
	GtkWidget *label_horizontal[LIMIT];
	node *left;
	node *right;
	node *parent;
};

node *root;

//Declaration of functions
int create_entry (GtkWidget *widget , gpointer frame);
void increase(GtkWidget *widget, gpointer label0);
void decrease(GtkWidget *widget, gpointer label0);
void size_fn (GtkWidget *widget, gpointer label_size);
void position_button(int dep,int i, node *tmp,gpointer frame);
void depth_fn (GtkWidget *widget, gpointer label_depth);
int reset(GtkWidget *widget, gpointer frame);
int delete_tree(node* temp);


/*Func for creating tree graphically*/
void position_button(int dep,int i,node *tmp,gpointer frame)
{
	/*Creation of tree graphically in GTK*/
	int j;
	
	if(dep>=0)
	{
			if (tmp->right!=NULL)
			{	
				/*of course, we have to destroy what was created*/
				for (j=0;j<3;j++)
					if (tmp->right->label_vertical[j]!=NULL)
						gtk_widget_destroy(tmp->right->label_vertical[j]);

				for(j=0;j<LIMIT;j++)
					if (tmp->right->label_horizontal[j]!=NULL)
						gtk_widget_destroy(tmp->right->label_horizontal[j]);
				
				/*Adjusting the button*/
				
				tmp->right->x=tmp->x+pow(2,dep)*WIDTH;
				y=25+70*i;
				gtk_fixed_put(GTK_FIXED(frame), tmp->right->b, tmp->right->x,y);
				gtk_widget_show(tmp->right->b);
				
				/*just for the vertical arrow*/
				tmp->right->label_vertical[0]=gtk_label_new("  | ");
				gtk_fixed_put(GTK_FIXED(frame), tmp->right->label_vertical[0], tmp->right->x+10,y-50);
				tmp->right->label_vertical[1]=gtk_label_new("  | ");
				gtk_fixed_put(GTK_FIXED(frame), tmp->right->label_vertical[1], tmp->right->x+10,y-35);
				tmp->right->label_vertical[2]=gtk_label_new("\\|/");
				gtk_fixed_put(GTK_FIXED(frame), tmp->right->label_vertical[2], tmp->right->x+10,y-20);
				gtk_widget_show(tmp->right->label_vertical[0]);
				gtk_widget_show(tmp->right->label_vertical[1]);
				gtk_widget_show(tmp->right->label_vertical[2]);

				/*just for the horizantal arrow*/
				tmp->right->label_horizontal[0]=gtk_label_new("----");
				gtk_fixed_put(GTK_FIXED(frame), tmp->right->label_horizontal[0], tmp->right->x,y-57);
				gtk_widget_show(tmp->right->label_horizontal[0]);
				
				for(j=1;j<pow(2,dep);j++)
				{
					tmp->right->label_horizontal[j]=gtk_label_new("----------");
					gtk_fixed_put(GTK_FIXED(frame), tmp->right->label_horizontal[j], tmp->right->x-(40+(j-1)*40),y-57);
					gtk_widget_show(tmp->right->label_horizontal[j]);
				}
			}			
			
			if (tmp->left!=NULL)
			{
				/*of course, we have to destroy what was created*/
				for (j=0;j<3;j++)
					if (tmp->left->label_vertical[j]!=NULL)
						gtk_widget_destroy(tmp->left->label_vertical[j]);
									
				for(j=0;j<LIMIT;j++)
					if (tmp->left->label_horizontal[j]!=NULL)
						gtk_widget_destroy(tmp->left->label_horizontal[j]);
				
				/*Adjusting the button*/
				
				tmp->left->x=tmp->x-pow(2,dep)*HEIGHT;
				y=25+70*i;
				gtk_fixed_put(GTK_FIXED(frame), tmp->left->b, tmp->left->x,y);
				gtk_widget_show(tmp->left->b);
			
				/*just for the vertical arrow*/
				tmp->left->label_vertical[0]=gtk_label_new("  | ");
				gtk_fixed_put(GTK_FIXED(frame), tmp->left->label_vertical[0], tmp->left->x+10,y-50);
				tmp->left->label_vertical[1]=gtk_label_new("  | ");
				gtk_fixed_put(GTK_FIXED(frame), tmp->left->label_vertical[1], tmp->left->x+10,y-35);
				tmp->left->label_vertical[2]=gtk_label_new("\\|/");
				gtk_fixed_put(GTK_FIXED(frame), tmp->left->label_vertical[2], tmp->left->x+10,y-20);
				gtk_widget_show(tmp->left->label_vertical[0]);
				gtk_widget_show(tmp->left->label_vertical[1]);
				gtk_widget_show(tmp->left->label_vertical[2]);
				
				
				/*just for the horizantal arrow*/
				tmp->left->label_horizontal[0]=gtk_label_new("-----");
				gtk_fixed_put(GTK_FIXED(frame), tmp->left->label_horizontal[0], tmp->left->x+20,y-57);
				gtk_widget_show(tmp->left->label_horizontal[0]);
				for(j=1;j<pow(2,dep);j++)
				{
					tmp->left->label_horizontal[j]=gtk_label_new("-----------");
					gtk_fixed_put(GTK_FIXED(frame), tmp->left->label_horizontal[j], tmp->left->x+(36+(j-1)*40),y-57);
					gtk_widget_show(tmp->left->label_horizontal[j]);
				}
			
			}
			if (tmp->left!=NULL)
				position_button(dep-1,i+1,tmp->left,frame);
			if (tmp->right!=NULL)
				position_button(dep-1,i+1,tmp->right,frame);
	}
	
}

/*Func for creating tree in memory*/
int create_entry (GtkWidget *widget , gpointer frame)
{
	int j=0;
	y=25;
	i=1;
	depth=0;
	node *tmp=root;
	size++;
	
	/* Creation of the tree in C */
	
	if(root==NULL)
	{
		root=(node*)malloc(sizeof(node));
		root->left=NULL;
		root->right=NULL;
		root->parent=NULL;
		for(j=0;j<3;j++)
			root->label_vertical[j]=NULL;
		for(j=0;j<LIMIT;j++)
			root->label_horizontal[j]=NULL;
		root->data=count;
		root->b=gtk_button_new_with_label(buf);
		root->x=800;
		gtk_widget_set_size_request(root->b, WIDTH,HEIGHT);
		gtk_fixed_put(GTK_FIXED(frame), root->b, root->x,y);
		gtk_widget_show(root->b);
	}	
	else
	{
		node* vertex=(node*)malloc(sizeof(node));
		vertex->left=NULL;
		vertex->right=NULL;
		vertex->parent=NULL;	
		for(j=0;j<3;j++)
			vertex->label_vertical[j]=NULL;
		for(j=0;j<LIMIT;j++)
			vertex->label_horizontal[j]=NULL;
		
		vertex->data=count;
		
		while(tmp!=NULL)		
		{			
			if(tmp->data < count)
			{
				depth++;
				if(tmp->right==NULL)
					break;
				tmp=tmp->right;
			}   
			else
			{
				depth++;
				if(tmp->left==NULL)
					break;
				tmp=tmp->left;			
			}
		}
				
		vertex->parent=tmp;
		
		if(tmp->data < count)
		{
			tmp->right=vertex;
			vertex->b=gtk_button_new_with_label(buf);
			gtk_widget_set_size_request(vertex->b, WIDTH,HEIGHT);
		}
		else
		{			
			tmp->left=vertex;
			vertex->b=gtk_button_new_with_label(buf);
			gtk_widget_set_size_request(vertex->b, WIDTH,HEIGHT);
		}
	}
	
	depth_record[size]=depth;
	
	for(j=1; j<size;j++)
	{
		if(depth<depth_record[j])
			depth=depth_record[j];
	}
	depth_max=depth;
	position_button(depth-1,1,root,frame);
	
	return 0;
}

/*Func to actually do the work of wiping out*/
int delete_tree(node *temp)
{
	node *temp2=NULL;
	int j;
	
	if(temp==NULL)
		return 0;
	
	if(temp->left!=NULL)
		delete_tree(temp->left);
	if(temp->right!=NULL)
		delete_tree(temp->right);
	
	temp2=temp->parent;
	gtk_widget_destroy(temp->b);
	for (j=0;j<3;j++)
		if (temp->label_vertical[j]!=NULL)
			gtk_widget_destroy(temp->label_vertical[j]);
	for(j=0;j<LIMIT;j++)
		if (temp->label_horizontal[j]!=NULL)
			gtk_widget_destroy(temp->label_horizontal[j]);
	free(temp);
	temp=NULL;
					
}

/* Callback Func for reset*/
int reset_tree(GtkWidget *widget, gpointer frame)
{
	int j;	//For loop
	
	if(root==NULL)
		return 0;
	else
		delete_tree(root);
			
	size=0;
	depth=0;
	depth_max=0;	
	for(j=0;j<200;j++)
		depth_record[200]=0;
	
	return 0;
}

/*Func for label change on clicking + */
void increase(GtkWidget *widget, gpointer label0)
{
	count++;

  	sprintf(buf, "%d", count);
  	gtk_label_set_text(GTK_LABEL(label0), buf);
}

/*Func for label change when clicking - */
void decrease(GtkWidget *widget, gpointer label0)
{
  	count--;

  	sprintf(buf, "%d", count);
  	gtk_label_set_text(GTK_LABEL(label0), buf);
}

void size_fn (GtkWidget *widget, gpointer label_size)
{
	sprintf(size_c, "%d", size); 
	gtk_label_set_text (GTK_LABEL(label_size), size_c);

}

void depth_fn (GtkWidget *widget, gpointer label_depth)
{
	sprintf(depth_c, "%d", depth_max); 
	gtk_label_set_text (GTK_LABEL(label_depth), depth_c);

}

int main (int argc, char *argv[])
{
	GtkWidget *window;
	GtkWidget *frame;
	GtkWidget *plus;
	GtkWidget *minus;
	GtkWidget *label0; //For + - thing
	GtkWidget *label_size[2];
	GtkWidget *label_depth[2];
	GtkWidget *insert;	
	GtkWidget *reset;
	
	//Some initialisation for create_tree function
	root=NULL;

	gtk_init(&argc,&argv);	//Start of GTK
	
	/*Setting up the window*/

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 1200, 600);
	gtk_window_set_title(GTK_WINDOW(window), "BINARY TREE");
	
	
	/*Setting up the frame*/

	frame = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window), frame);


	/*Creating buttons*/

	plus = gtk_button_new_with_label("+");
	gtk_widget_set_size_request(plus, 35,35);
	gtk_fixed_put(GTK_FIXED(frame), plus, 40, 50);

	minus = gtk_button_new_with_label("-");
	gtk_widget_set_size_request(minus, 35, 35);
	gtk_fixed_put(GTK_FIXED(frame), minus, 40, 110);

	/*Creating labels*/
	
	label0 = gtk_label_new ("0");
	gtk_fixed_put(GTK_FIXED(frame), label0, 150, 88);
	
	label_size[0]= gtk_label_new ("Size :- ");
	gtk_fixed_put (GTK_FIXED (frame) , label_size[0] ,40,520);
	
	label_size[1]= gtk_label_new ("0");
	gtk_fixed_put (GTK_FIXED (frame) , label_size[1] ,90,520);

	label_depth[0]= gtk_label_new ("Depth :- ");
	gtk_fixed_put (GTK_FIXED (frame) , label_depth[0] ,40,550);
	
	label_depth[1]= gtk_label_new ("0");
	gtk_fixed_put (GTK_FIXED (frame) , label_depth[1] ,100,550);
	
	/*Insert and reset button*/

	insert=gtk_button_new_with_label("Insert");
	gtk_widget_set_size_request(insert, 90,45);
	gtk_fixed_put(GTK_FIXED(frame), insert, 90, 170);
	
	reset=gtk_button_new_with_label("Reset");
	gtk_widget_set_size_request(reset, 90,45);
	gtk_fixed_put(GTK_FIXED(frame), reset, 90, 270);
	
	//Show command
	gtk_widget_show_all(window);

	/*destroy signal*/
	g_signal_connect(window, "destroy",
		G_CALLBACK(gtk_main_quit), NULL);

	/*If Button is clicked*/
	g_signal_connect(plus, "clicked", 
      		G_CALLBACK(increase), label0);

	g_signal_connect(minus, "clicked", 
      		G_CALLBACK(decrease), label0);
          
  	g_signal_connect(insert, "clicked",
        	G_CALLBACK(create_entry), frame);
        	      
    g_signal_connect(insert, "clicked",
        G_CALLBACK(size_fn), label_size[1]);	
     	
  	g_signal_connect(insert, "clicked",
        	G_CALLBACK(depth_fn), label_depth[1]);

  	g_signal_connect(reset, "clicked",
        	G_CALLBACK(reset_tree), frame);
       
	g_signal_connect(reset,"clicked",
			G_CALLBACK(size_fn), label_size[1]);
			
	g_signal_connect(reset,"clicked",
			G_CALLBACK(depth_fn), label_depth[1]);
			
	gtk_main();
	
	return 0;
}