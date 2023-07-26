#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LEN 50


typedef struct student_record
{
	int student_id;
	char name[MAX_LEN];
	char group_partner[MAX_LEN];
	int group_id;
	char assignment_name_id[MAX_LEN];
	char deadline[MAX_LEN];
	char status[MAX_LEN];
	float offline_marks;
	float viva_marks;
	int ht;
	
	struct student_record* left;
	struct student_record* right;
	
}Node1;


typedef struct assignment_record
{
	int assignment_id;
	char topic_name[MAX_LEN];
	char status[MAX_LEN];
	struct StudentAssignmentRecord* student_group;
	int ht;
	
	struct assignment_record* left;
	struct assignment_record* right;
}Node2;


typedef struct StudentAssignmentRecord 
{
    int student_group_id;
    char status[MAX_LEN];
    float marks_given;
    int ht;
    
    struct StudentAssignmentRecord* left;
    struct StudentAssignmentRecord* right;
}Node3;


Node1* student = NULL ;
Node2* assignment = NULL ;


Node1* create_student(int student_id,char* name,char* group_partner,int group_id,char* assignment_name_id,char* deadline,char* status,float offline_marks,float viva_marks)
{
	Node1* nptr = (Node1*)malloc(sizeof(Node1));
	
	nptr->student_id = student_id;
	strcpy(nptr->name , name);
	strcpy(nptr->group_partner , group_partner);
	nptr->group_id = group_id;
	strcpy(nptr->assignment_name_id , assignment_name_id);
	strcpy(nptr->deadline , deadline);
	strcpy(nptr->status , status);
	nptr->offline_marks = offline_marks;
	nptr->viva_marks = viva_marks;
	nptr->left = NULL;
	nptr->right = NULL;
	nptr->ht = 1;
	
	return nptr;
}

Node2* create_assignment(int assignment_id , char* topic_name)
{
	Node2* nptr = (Node2*)malloc(sizeof(Node2));
	
	nptr->assignment_id = assignment_id;
	strcpy(nptr->topic_name , topic_name);
	strcpy(nptr->status , "Declared");
	nptr->student_group = NULL;
	nptr->right = NULL;
	nptr->left = NULL;
	nptr->ht= 1;
	
	return nptr;
}

float maxi(float a , float b)
{
	if(a>=b)
	{
		return a;
	}
	return b;
}

Node3* create_student_group(int student_group_id , char* status , float offline_marks1 , float viva_marks1 , float offline_marks2 , float viva_marks2)
{
	Node3* nptr = (Node3*) malloc(sizeof(Node3));
	
	nptr->student_group_id = student_group_id;
	strcpy(nptr->status, status);
	nptr->marks_given = maxi(offline_marks1+viva_marks1 , offline_marks2+viva_marks2);
	nptr->right = NULL;
	nptr->left = NULL;
	nptr->ht = 1;
	
	return nptr;
}







////Traversing Functions ----------->>>>>

void visit_1(Node1* ptr)
{
	printf("%d \n",ptr->student_id);
	printf("%s\n",ptr->name);
	printf("%s\n",ptr->group_partner);
	printf("%d \n",ptr->group_id);
	printf("%s\n",ptr->assignment_name_id);
	printf("%s\n",ptr->deadline);
	printf("%s\n",ptr->status);
	printf("%f\n",ptr->offline_marks);
	printf("%f\n",ptr->viva_marks);
	printf("-----------\n");
}

void inOrder_1(Node1* student)
{
	Node1* root = student;
	if(root!=NULL)
	{
		inOrder_1(root->left);
		visit_1(root);
		inOrder_1(root->right);
	}
}

void visit_3(Node3* ptr)
{
	printf("		%d \n",ptr->student_group_id);
	printf("		%s\n",ptr->status);
	printf("		%f\n",ptr->marks_given);
	printf("        ----------\n");
}

void inOrder_3(Node3* ptr)
{
	Node3* root = ptr;
	if(root!=NULL)
	{
		inOrder_3(root->left);
		visit_3(root);
		inOrder_3(root->right);
	}
}

void visit_2(Node2* ptr)
{
	printf("%d \n",ptr->assignment_id);
	printf("%s\n",ptr->topic_name);
	printf("%s\n",ptr->status);
	inOrder_3(ptr->student_group);
	printf("-----------\n");
}

void inOrder_2(Node2* assignment)
{
	Node2* root = assignment;
	if(root!=NULL)
	{
		inOrder_2(root->left);
		visit_2(root);
		inOrder_2(root->right);
	}
}











/////Function for Node1

Node1* search_1(Node1* root, int key)
{
    if (root == NULL)
    {
        return NULL;
    }
 
    if(root->student_id == key)
    {
        return root;
    }
 
    if(key > root->student_id)
    {
        search_1(root->right, key);
    }
    else
    {
        search_1(root->left, key);
    } 
}

// rotates to the left
Node1* rotate_left_1(Node1* root)
{
    Node1* right_child = root->right;
    root->right = right_child->left;
    right_child->left = root;
 
    // update the heights of the nodes
    root->ht = height_1(root);
    right_child->ht = height_1(right_child);
 
    // return the new node after rotation
    return right_child;
}
 
// rotates to the right
Node1* rotate_right_1(Node1* root)
{
    Node1* left_child = root->left;
    root->left = left_child->right;
    left_child->right = root;
 
    // update the heights of the nodes
    root->ht = height_1(root);
    left_child->ht = height_1(left_child);
 
    // return the new node after rotation
    return left_child;
}
 
// calculates the balance factor of a node
int balance_factor_1(Node1* root)
{
    int lh, rh;
    if (root == NULL)
        return 0;
    if (root->left == NULL)
        lh = 0;
    else
        lh = 1 + root->left->ht;
    if (root->right == NULL)
        rh = 0;
    else
        rh = 1 + root->right->ht;
    return lh - rh;
}

int height_1(Node1* root)
{
    int lh, rh;
    if (root == NULL)
    {
        return 0;
    }
    if (root->left == NULL)
        lh = 0;
    else
        lh = 1 + root->left->ht;
    if (root->right == NULL)
        rh = 0;
    else
        rh = 1 + root->right->ht;
 
    if (lh > rh)
        return (lh);
    return (rh);
}

Node1* insert_1(Node1* root, Node1* new_node)
{
	int student_id = new_node->student_id;
	
    if (root == NULL)
    {
        //Node1* new_node = create(student_id);
        if (new_node == NULL)
        {
            return NULL;
        }
        root = new_node;
    }
    else if (student_id > root->student_id)
    {
        // insert the new node to the right
        root->right = insert_1(root->right, new_node);
 
        // tree is unbalanced, then rotate it
        if (balance_factor_1(root) == -2)
        {
            if (student_id > root->right->student_id)
            {
                root = rotate_left_1(root);
            }
            else
            {
                root->right = rotate_right_1(root->right);
                root = rotate_left_1(root);
            }
        }
    }
    else
    {
        // insert the new node to the left
        root->left = insert_1(root->left, new_node);
 
        // tree is unbalanced, then rotate it
        if (balance_factor_1(root) == 2)
        {
            if (student_id < root->left->student_id)
            {
                root = rotate_right_1(root);
            }
            else
            {
                root->left = rotate_left_1(root->left);
                root = rotate_right_1(root);
            }
        }
    }
    // update the heights of the nodes
    root->ht = height_1(root);
    return root;
}














/////Functions for Node2

Node2* search_2(Node2* root, int key)
{
    if (root == NULL)
    {
        return NULL;
    }
 
    if(root->assignment_id == key)
    {
        return root;
    }
 
    if(key > root->assignment_id)
    {
        search_2(root->right, key);
    }
    else
    {
        search_2(root->left, key);
    } 
}

// rotates to the left
Node2* rotate_left_2(Node2* root)
{
    Node2* right_child = root->right;
    root->right = right_child->left;
    right_child->left = root;
 
    // update the heights of the nodes
    root->ht = height_2(root);
    right_child->ht = height_2(right_child);
 
    // return the new node after rotation
    return right_child;
}
 
// rotates to the right
Node2* rotate_right_2(Node2* root)
{
    Node2* left_child = root->left;
    root->left = left_child->right;
    left_child->right = root;
 
    // update the heights of the nodes
    root->ht = height_2(root);
    left_child->ht = height_2(left_child);
 
    // return the new node after rotation
    return left_child;
}
 
// calculates the balance factor of a node
int balance_factor_2(Node2* root)
{
    int lh, rh;
    if (root == NULL)
        return 0;
    if (root->left == NULL)
        lh = 0;
    else
        lh = 1 + root->left->ht;
    if (root->right == NULL)
        rh = 0;
    else
        rh = 1 + root->right->ht;
    return lh - rh;
}

int height_2(Node2* root)
{
    int lh, rh;
    if (root == NULL)
    {
        return 0;
    }
    if (root->left == NULL)
        lh = 0;
    else
        lh = 1 + root->left->ht;
    if (root->right == NULL)
        rh = 0;
    else
        rh = 1 + root->right->ht;
 
    if (lh > rh)
        return (lh);
    return (rh);
}

Node2* insert_2(Node2* root, Node2* new_node)
{
	int assignment_id = new_node->assignment_id;
	
    if (root == NULL)
    {
        //Node1* new_node = create(student_id);
        if (new_node == NULL)
        {
            return NULL;
        }
        root = new_node;
    }
    else if (assignment_id > root->assignment_id)
    {
        // insert the new node to the right
        root->right = insert_2(root->right, new_node);
 
        // tree is unbalanced, then rotate it
        if (balance_factor_2(root) == -2)
        {
            if (assignment_id > root->right->assignment_id)
            {
                root = rotate_left_2(root);
            }
            else
            {
                root->right = rotate_right_2(root->right);
                root = rotate_left_2(root);
            }
        }
    }
    else
    {
        // insert the new node to the left
        root->left = insert_2(root->left, new_node);
 
        // tree is unbalanced, then rotate it
        if (balance_factor_2(root) == 2)
        {
            if (assignment_id < root->left->assignment_id)
            {
                root = rotate_right_2(root);
            }
            else
            {
                root->left = rotate_left_2(root->left);
                root = rotate_right_2(root);
            }
        }
    }
    // update the heights of the nodes
    root->ht = height_2(root);
    return root;
}











/////Functions for Node3

Node3* search_3_1(Node3* root , float key , int grp_id)
{
	if (root == NULL)
    {
        return NULL;
    }
 
    if(root->marks_given == key && root->student_group_id == grp_id)
    {
        return root;
    }
 
    if(key > root->marks_given)
    {
        search_3_1(root->right, key,grp_id);
    }
    else
    {
        search_3_1(root->left, key,grp_id);
    }
}

Node3* search_3(Node3* root, float key)
{
    if (root == NULL)
    {
        return NULL;
    }
 
    if(root->marks_given == key)
    {
        return root;
    }
 
    if(key > root->marks_given)
    {
        search_3(root->right, key);
    }
    else
    {
        search_3(root->left, key);
    } 
}

// rotates to the left
Node3* rotate_left_3(Node3* root)
{
    Node3* right_child = root->right;
    root->right = right_child->left;
    right_child->left = root;
 
    // update the heights of the nodes
    root->ht = height_3(root);
    right_child->ht = height_3(right_child);
 
    // return the new node after rotation
    return right_child;
}
 
// rotates to the right
Node3* rotate_right_3(Node3* root)
{
    Node3* left_child = root->left;
    root->left = left_child->right;
    left_child->right = root;
 
    // update the heights of the nodes
    root->ht = height_3(root);
    left_child->ht = height_3(left_child);
 
    // return the new node after rotation
    return left_child;
}
 
// calculates the balance factor of a node
int balance_factor_3(Node3* root)
{
    int lh, rh;
    if (root == NULL)
        return 0;
    if (root->left == NULL)
        lh = 0;
    else
        lh = 1 + root->left->ht;
    if (root->right == NULL)
        rh = 0;
    else
        rh = 1 + root->right->ht;
    return lh - rh;
}

int height_3(Node3* root)
{
    int lh, rh;
    if (root == NULL)
    {
        return 0;
    }
    if (root->left == NULL)
        lh = 0;
    else
        lh = 1 + root->left->ht;
    if (root->right == NULL)
        rh = 0;
    else
        rh = 1 + root->right->ht;
 
    if (lh > rh)
        return (lh);
    return (rh);
}

Node3* insert_3(Node3* root, Node3* new_node)
{
	float marks_given = new_node->marks_given;
	
    if (root == NULL)
    {
        //Node1* new_node = create(student_id);
        if (new_node == NULL)
        {
            return NULL;
        }
        root = new_node;
    }
    else if (marks_given > root->marks_given)
    {
        // insert the new node to the right
        root->right = insert_3(root->right, new_node);
 
        // tree is unbalanced, then rotate it
        if (balance_factor_3(root) == -2)
        {
            if (marks_given > root->right->marks_given)
            {
                root = rotate_left_3(root);
            }
            else
            {
                root->right = rotate_right_3(root->right);
                root = rotate_left_3(root);
            }
        }
    }
    else
    {
        // insert the new node to the left
        root->left = insert_3(root->left, new_node);
 
        // tree is unbalanced, then rotate it
        if (balance_factor_3(root) == 2)
        {
            if (marks_given < root->left->marks_given)
            {
                root = rotate_right_3(root);
            }
            else
            {
                root->left = rotate_left_3(root->left);
                root = rotate_right_3(root);
            }
        }
    }
    // update the heights of the nodes
    root->ht = height_3(root);
    return root;
}








//Question 1 ------------------->>>>>

Node1* insert_student(Node1* student,int student_id1,int student_id2,char* name,char* group_partner,int group_id,char* assignment_name_id,char* deadline,char* status,float offline_marks1,float viva_marks1,float offline_marks2,float viva_marks2,int assignment_id)
{
	Node1* nptr1 = create_student(student_id1,name,group_partner,group_id,assignment_name_id,deadline,status,offline_marks1,viva_marks1);
	Node1* nptr2 = create_student(student_id2,group_partner,name,group_id,assignment_name_id,deadline,status,offline_marks2,viva_marks2);
	
	if(search_1(student,student_id1) || search_1(student,student_id2))
	{
		printf("Student with same id already exists \n\n");
	}
	else
	{
		student = insert_1(student,nptr1);
		student = insert_1(student,nptr2);
		
		//Checking in Assignment Record ---------->>>>>
		
		Node2* ptr = assignment;
		Node2* found = search_2(ptr,assignment_id);
		
		if(found == NULL)
		{
			Node2* nptr = create_assignment(assignment_id , assignment_name_id );
			assignment = insert_2(assignment , nptr);
		}
		
		// Adding student groups ------->>>
		
		
		Node3* nptr3 = create_student_group(group_id ,status ,offline_marks1 ,viva_marks1 ,offline_marks2 ,viva_marks2);
		ptr = search_2(assignment , assignment_id);
		
		ptr->student_group = insert_3(ptr->student_group , nptr3);
		
	}
	
	return student;
}





//// Question 2 --------------->>>>

Node2* insert_assignment(Node1** student , Node2* assignment , char* topic_name , int assignment_id , int* student_id , char* name[] , int* group_id , char* deadline , char** status , float* offline_marks , float* viva_marks , int num_stud )
{
	Node2* nptr = create_assignment(assignment_id , topic_name );
	
	Node2* ptr = assignment;
	Node2* found = search_2(ptr,assignment_id);
	
	if(found != NULL)
	{
		printf("An assignment with same id already exists \n\n");
	}
	else
	{
		if(found == NULL)
		{
			assignment = insert_2(assignment , nptr);
		}
		
		
		////Insert student grps ------------>>>>
		int i;
		for(i=0;i<num_stud;i+=2)
		{
			Node3* nptr3 = create_student_group(group_id[i] , status[i] ,offline_marks[i] ,viva_marks[i] ,offline_marks[i+1] ,viva_marks[i+1]);
			
			nptr->student_group = insert_3(nptr->student_group , nptr3);
		}
		
		
		////Insert student records ------------>>>>
		for(i=0;i<num_stud;i+=2)
		{
			//Node1* ptri = student;
			Node1* nptr1 = create_student(student_id[i],name[i],name[i+1],group_id[i],topic_name,deadline,status[i],offline_marks[i],viva_marks[i]);
			Node1* nptr2 = create_student(student_id[i+1],name[i+1],name[i],group_id[i+1],topic_name,deadline,status[i],offline_marks[i+1],viva_marks[i+1]);
			
			if(search_1(*student,nptr1->student_id) || search_1(*student,nptr2->student_id))
			{
				printf("Student with same id already exists \n\n");
			}
			else
			{
				*student = insert_1(*student,nptr1);
				*student = insert_1(*student,nptr2);
			}
		}
	}
	return assignment;
}







//// Question 3 --------------->>>>


int flag = 1;

int check_status(Node3* root)
{
	if(root!=NULL)
	{
		check_status(root->left );
		
		if(strcmp(root->status , "Evaluated") != 0)
		{
			flag = 0;
		}
		
		check_status(root->right );
	}
	
	return flag;	
}

void check_asg_grp(Node2* root)
{
	int a;
	if(root!=NULL)
	{
		check_asg_grp(root->left);
		
		flag = 1;
		a = check_status(root->student_group);
		if(a == 1)
		{
			strcpy(root->status , "Evaluated");
		}
		
		check_asg_grp(root->right);
	}
}

void change_status(Node1* student , Node2* assignment , int student_id1 , int student_id2 , char* status ,float offline_marks1 , float viva_marks1 , float offline_marks2 , float viva_marks2 , int asg_id)
{
	//Node1* ptr = student;
	float marks ;
	int grp_id ;
	Node1* ptr1 = search_1(student , student_id1);
	Node1* ptr2 = search_1(student , student_id2);
	if(ptr1!=NULL && ptr2!=NULL)
	{
		grp_id = ptr1->group_id;
		marks  = maxi(ptr1->offline_marks+ptr1->viva_marks , ptr2->offline_marks+ptr2->viva_marks);
		
		strcpy(ptr1->status , status);
		ptr1->offline_marks = offline_marks1;
		ptr1->viva_marks = viva_marks1;
		
		strcpy(ptr2->status , status);
		ptr2->offline_marks = offline_marks2;
		ptr2->viva_marks = viva_marks2;
		
	}
	
	
	//// Changing in student group records 
	Node2* ptr = assignment;
	Node2* nptr = search_2(assignment , asg_id);
	if(nptr!=NULL)
	{
		Node3* ptr3 = search_3_1(nptr->student_group , marks , grp_id);
		if(ptr3->student_group_id = grp_id)
		{
			strcpy(ptr3->status , status);
			ptr3->marks_given = maxi(offline_marks1+viva_marks1 , offline_marks2+viva_marks2);
		}
	}
	
	
	/// Changing status of Assignment
	
	check_asg_grp(assignment);
	
}






void change_status_asg_duedate(Node2* assignment , int asg_id)
{
	Node2* ptr = assignment;
	Node2* ptr1 = search_2(assignment , asg_id);
	
	strcpy(ptr->status , "DueDateOver");

	check_asg_grp(assignment);

}




////// Question 4 ------------------->>>>

void print_declared_not_eval(Node2* root)
{
	Node2* ptr = root;
	if(ptr!=NULL)
	{
		print_declared_not_eval(ptr->left);
		
		if(strcmp(ptr->status , "Evaluated") != 0 && strcmp(ptr->status , "DueDateOver") !=0)
		{
			printf("\nAssignment id : %d\n",ptr->assignment_id);
			printf("Topic Name : %s\n",ptr->topic_name);
			printf("Status : %s\n",ptr->status);
			printf("-----------\n");
		}
		
		print_declared_not_eval(ptr->right);
	}
}







/////Question 5 ------------------->>>>>

int found = 0;
void check_q5(Node3* root)
{
	Node3* ptr = root;
	if(ptr!=NULL)
	{
		check_q5(ptr->left);
		
		if(strcmp(ptr->status , "NotSubmitted") == 0)
		{
			printf("		Group id : %d\n",ptr->student_group_id);
			printf("        Status   : %s\n",ptr->status);
			found = 1;
		}
		
		check_q5(ptr->right);
	}
}

void print_stud_not_submitted(Node2* assignment , Node1* student)
{
	Node2* ptr = assignment;
	if(ptr!=NULL)
	{
		print_stud_not_submitted(ptr->left , student);
		
		if(strcmp(ptr->status , "DueDateOver") == 0)
		{
			printf("\nAssignment id : %d\n",ptr->assignment_id);
			printf("Topic Name : %s\n",ptr->topic_name);
			printf("Status : %s\n\n",ptr->status);
			
			Node3* ptr2 = ptr->student_group;
			if(ptr2!=NULL)
			{
				check_q5(ptr2);
				if(found == 0)
				{
					printf("        No One\n");
				}
				printf("------------------------------\n\n");
			}
		}
		
		print_stud_not_submitted(ptr->right , student);
	}
}









///// Question 6 ---------------------->>>>

void print_stud_notEval_sub(Node1* root)
{
	Node1* ptr = root;
	if(ptr!=NULL)
	{
		print_stud_notEval_sub(ptr->left);
		
		if(strcmp(ptr->status , "Submitted") == 0)
		{
			printf("\nGroup id : %d\n",ptr->group_id);
			printf("Assignment Topic : %s\n",ptr->assignment_name_id);
			printf("Member 1 : %s\n",ptr->name);
			printf("Member 2 : %s\n",ptr->group_partner);
			printf("Submitted but not Evaluated\n\n\n");
		}
		else if(strcmp(ptr->status , "Evaluated") == 0)
		{
			if(ptr->viva_marks == 0)
			{
				printf("Group id : %d\n",ptr->group_id);
				printf("Assignment Topic : %s\n",ptr->assignment_name_id);
				printf("Member 1 : %s\n",ptr->name);
				printf("Member 2 : %s\n",ptr->group_partner);
				printf("Evaluated but Viva is Not Yet Completed\n\n\n");
			}
		}
		
		print_stud_notEval_sub(ptr->right);
	}
}







//////Question 7 --------------------->>>>

void print_dec_order(Node2* assignment , int assignment_id)
{
	Node2* ptr = search_2(assignment , assignment_id);
	if(ptr == NULL)
	{
		printf("No such assignment\n\n");
	}
	else
	{
		Node3* ptr1 = ptr->student_group;
		printf("\nAssignment id : %d\n",ptr->assignment_id);
		printf("Topic Name    : %s\n",ptr->topic_name);
		
		inOrder_3(ptr1);
	}
}






///// Question 8 ---------------------->>>>


Node3* get_rightmost_node(Node3* root)
{
	if(root!=NULL)
	{
		if(root->right == NULL)
		{
			return root;
		}
		if(root->right!=NULL)
		{
			return get_rightmost_node(root->right);
		}
	}
}

void print_top_stud(Node2* root)
{
	Node2* ptr = root;
	if(ptr!=NULL)
	{
		print_top_stud(ptr->left);
		
		printf("\nAssignment id : %d\n",ptr->assignment_id);
		printf("Topic Name : %s\n",ptr->topic_name);
		Node3* ptr1 = ptr->student_group;
		Node3* right_node = get_rightmost_node(ptr1);
		printf("		Group id : %d\n",right_node->student_group_id);
		printf("		Top Marks Given : %f\n\n\n",right_node->marks_given);
		
		print_top_stud(ptr->right);
	}

}








/////Question 9 ------------------->>>>


void range_search(Node2* root , int a1 , int a2)
{
	if(root!=NULL)
	{
		range_search(root->left , a1, a2);
		
		if(a1 < root->assignment_id && a2 > root->assignment_id)
		{
			printf("%d \n",root->assignment_id);
			printf("%s\n",root->topic_name);
			printf("%s\n",root->status);
			inOrder_3(root->student_group);
			printf("-----------\n");
		}
		
		range_search(root->right , a1, a2);
	}
}












void Display_Marks(int student_id)
{
	Node1* ptr = search_1(student , student_id);
	if(ptr!=NULL)
	{
		printf("%d \n",ptr->student_id);
		printf("%s\n",ptr->name);
		printf("%s\n",ptr->status);
		printf("%f\n",ptr->offline_marks);
		printf("%f\n\n",ptr->viva_marks);
		printf("--------------\n\n");
	}
	else
	{
		printf("No such student\n\n");
	}
}



void Display_grp_details(int student_id)
{
	Node1* ptr = search_1(student , student_id);
	if(ptr!=NULL)
	{
		printf("%d \n",ptr->student_id);
		printf("%s\n",ptr->name);
		printf("%s\n",ptr->group_partner);
		printf("%d \n",ptr->group_id);
		printf("%s\n",ptr->assignment_name_id);
		printf("%s\n",ptr->deadline);
		printf("%s\n",ptr->status);
		printf("%f\n",ptr->offline_marks);
		printf("%f\n\n",ptr->viva_marks);
		printf("--------------\n\n");
	}
	else
	{
		printf("No such student\n\n");
	}
}




//int main()
//{
//	student = insert_student(student , 1 , 2 , "Dinesh" , "Dino" , 11 , "Strings" , "23-01-23" , "Submiited" , 0 , 0 , 0 , 0 , 101);
//	inOrder_1(student);
//	printf("\n");
//	inOrder_2(assignment);
//	printf("\n");
//	student = insert_student(student , 3 , 4 , "Din" , "Di" , 13 , "Strings" , "23-01-23" , "Submiited" , 0 , 0 , 0 , 0 , 101);
//	inOrder_1(student);
//	printf("\n");
//	inOrder_2(assignment);
//	printf("\n");
//}






int main()
{
	FILE *fp;
    fp = fopen("input.txt", "r");

    if (fp == NULL)
    {
        printf("Can't open file for reading.\n");
        return 0;
    }
	do
	{
		int a;
		printf("Choose the correct choice :\n");
		printf("1. Student\n");
		printf("2. Teacher\n");
		printf("3. Exit Program\n");
		//printf("Enter your choice : ");
		//scanf("%d",&a);
		fscanf(fp, "%d", &a);
		if(a==3)
		{
			printf("\n\nExiting Program\n\n");
			break;
		}
		switch(a)
		{
			char name[MAX_LEN] ;
			int password ,found;
			Node1* ptr;
			int key;
			case 1 :
			{
				printf("\n\nYou choose 1 \n\n");
				printf("------------------Students Portal-------------------\n");
				found = 0;
				//printf("Enter your Name : ");
//				scanf("%s",name);
//				printf("Enter your Password (Password is same as of your student_id) : ");
//				scanf("%d",&password);
				fscanf(fp,"%s",name);
				fscanf(fp,"%d",&password);
				printf("%s %d",name,password);
				ptr = search_1(student,password);
				if(ptr!=NULL)
				{
					printf("\nValidated\n\n");
					
						do
						{
							int b;
							printf("\n\nChoose the correct choice :\n");
							printf("1. Display your Marks\n");
							printf("2. Display your Group Details\n");
							printf("3. Exit this block\n\n");
							printf("Enter your choice : ");
							fscanf(fp,"%d",&b);
							if(b==3)
							{
								printf("\n\nExiting this block\n\n");
								break;
							}
							switch(b)
							{
								int id;
								case 1 :
									printf("\n\nYou choose 1 \n\n");
									//printf("Enter your Group id : ");
									//scanf("%d",&id);
									Display_Marks(password);
									//printf("Hi\n");
									break;
								case 2 :
									printf("\n\nYou choose 2 \n\n");
									Display_grp_details(password);
									
									break;
								default : 
									printf("\n\nInvalid Choice\n");	
									break;
							}
						}while(1);
						break;
				}
			}
			char name2[MAX_LEN] ;
			char password1[MAX_LEN] ;
			case 2 :
			{
				printf("\n\nYou choose 2 \n\n");
				printf("\n\n------------------Teachers Portal-------------------\n");
				//printf("Enter your Name : ");
				//scanf("%s",name2);
				fscanf(fp, "%s %s", name2, password1);
				//printf("%s\n",name2);
				//printf("Enter your Password (all small letters) : ");
				//scanf("%s",password1);
				//printf("%s\n",password1);
				//printf("Hi");
				if(strcmp(name2, "Keskar") == 0 && strcmp(password1, "keskar") == 0 )
				{
					printf("\n\nValidated\n");
					do
					{
						int b;
						printf("\n\nChoose the correct choice :\n");
						printf("1. Insert Student Record\n");
						printf("2. Insert Assignment\n");
						printf("3. Change Status\n");
						printf("4. Print List of Assignments declared but not Evaluated\n");
						printf("5. Print the list student groups who have not submitted the assignments even if the due-date is over. \n");
						printf("6. Print the list of student groups for whom the assignment is yet-to-be-evaluated even though they have been submitted.\n");
						printf("7. Print the details of student-groups, in the decreasing order of marks for a particular assignment\n");
						printf("8. Print student groups receiving top marks in each of the assignment given.\n");
						printf("9. Range Search between 2 assignments\n");
						printf("10. Exit this Block\n\n");
 						printf("Enter your choice : ");
						//scanf("%d",&b);
						fscanf(fp, "%d", &b);
						if(b==10)
						{
							printf("\n\nExiting this block\n\n");
							break;
						}
						switch(b)
						{
							int c,d,h,o;
							char e[MAX_LEN],f[MAX_LEN],g[MAX_LEN],i[MAX_LEN],j[MAX_LEN];
							float k,l,m,n;
							case 1 :
							{
								printf("\n\nInserting student record-------->\n");
								//printf("Enter the both student ids and names : ");
								fscanf(fp,"%d %d %s %s",&c,&d,e,f);
								//printf("\nEnter group id : ");
								fscanf(fp,"%d",&o);
								//printf("\nEnter asg name and id");
								fscanf(fp,"%s %d",g,&h);
								//printf("\nEnter deadline and status : ");
								fscanf(fp,"%s %s",i,j);
	    						//printf("\nEnter offline and viva marks of both students : ");
								fscanf(fp,"%f %f %f %f",&k,&l,&m,&n);
								
								student = insert_student(student,c,d,e,f,o,g,i,j,k,l,m,n,h);
								inOrder_1(student);
								break;
							}
							int num,p,asg_id;
							char deadline[MAX_LEN] ; 
							char topic_name[MAX_LEN];
							int stud_id[100];
							int grp_id[100];
							char name[100][MAX_LEN];
							char status[100][MAX_LEN];
							float off_marks[100] ;
							float viva_marks[100];
							char *name_pointers[100];
							char *status_pointers[100];
							case 2 :
							{
								printf("\n\nInserting Assignment record---------->\n");
								//printf("Enter Assignment id , Topic name and deadline respectively : ");
								fscanf(fp,"%d %s %s",&asg_id,topic_name,deadline);
								
								//printf("Enter number of students : ");
								fscanf(fp,"%d",&num);
								//char* topic_name , int assignment_id , int* student_id , char** name , int* group_id , char* deadline , char** status , float* offline_marks , float* viva_marks , int num_stud
								for(p=0;p<num;p++)
								{
									//printf("Enter student id , Name , Group Id , Status , Offline and viva marks respectively : \n");
									fscanf(fp,"%d %s %d %s %f %f",&stud_id[p],name[p],&grp_id[p],status[p],&off_marks[p],&viva_marks[p]);
									name_pointers[p]=name[p];
									status_pointers[p]=status[p];
								}
								
								assignment = insert_assignment(&student , assignment ,topic_name, asg_id,stud_id,name_pointers,grp_id,deadline,status_pointers,off_marks,viva_marks,num);
								printf("-----\n");
								inOrder_1(student);
								printf("-----\n");
								inOrder_2(assignment);
								break;
							}
							int s1,s2,assig_id;
							char stat[MAX_LEN];
							float m1,m2,m3,m4;
							case 3 :
							{
								printf("\n\nChanging status of a group ----------->\n");
								//printf("Enter the group id , Assignment id and status : ");
								fscanf(fp,"%d %d %d %s",&s1,&s2,&assig_id,stat);
								//printf("%d %s",group_id,stat);
								if(strcmp(stat , "Evaluated") != 0)
								{
									change_status(student,assignment,s1,s2,stat,0,0,0,0,assig_id);
								}
								else if(strcmp(stat , "Evaluated") == 0 )
								{
									//printf("Enter offline and viva marks of both students respectively : ");
									fscanf(fp,"%f %f %f %f",&m1,&m2,&m3,&m4);
									//printf("%f %f %f %f",m1,m2,m3,m4);
									change_status(student,assignment,s1,s2,stat,m1,m2,m3,m4,assig_id);
								}
								printf("-----\n");
								inOrder_1(student);
								printf("-----\n");
								inOrder_2(assignment);
								
								printf("\n\nChanging status of assignment to DueDateover\n");
								change_status_asg_duedate(assignment ,  assig_id);
								printf("-----\n");
								inOrder_2(assignment);
								
								break;
							}
							case 4 :
							{
								printf("\n\nPrinting List of Assignments declared but not evaluated--------->\n");
								print_declared_not_eval(assignment);
								break;
							}
							case 5 :
							{
								printf("\n\nPrinting the list student groups who have not submitted the assignments even if the due-date is over.\n");
								print_stud_not_submitted(assignment , student);
								break;
							}
							case 6 :
							{
								printf("\n\nPrinting the list of student groups for whom the assignment is yet-to-be-evaluated even though they have been submitted.\n");
								print_stud_notEval_sub(student);
								break;
							}
							int assignment_id;
							case 7 :
							{
								printf("\n\nPrinting the details of student-groups, in the Increasing order of marks for a particular assignment\n");
								//printf("Enter Assignment id : ");
								fscanf(fp,"%d",&assignment_id);
								print_dec_order(assignment , assignment_id);
								break;
							}
							case 8 :
							{
								printf("\n\nPrinting student groups receiving top marks in each of the assignment given.\n");
								print_top_stud(assignment);
								break;
							}
							int a1,a2;
							case 9 :
							{
								printf("\n\nRange Search\n");
								fscanf(fp,"%d %d",&a1,&a2);
								range_search(assignment,a1,a2);
							}
							case 10 :
							{
								break;
							}
							default :
							{
								printf("\n\nEnter valid Number \n");
								break;
							}
						}
					}while(1);
				}
				else
				{
					printf("\n\nIncorrect Password\n");
					exit(0);
				}
				break;
			}
			case 3 :
				break;
			default :
				printf("\n\nEnter Valid Number\n\n");	
				break;
		}
	}while(1);
	fclose(fp);
	return 0;
}
