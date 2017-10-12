#include<stdio.h>
#include<conio.h>
#define ARY 7
#define MAXKEYS (ARY - 1)
#define MINKEYS ((ARY + 1)/2 - 1)
typedef int Key_Type;
typedef struct Employee_Tag
        {
            Key_Type Emp_Num;
            char Emp_Name[50];
            char Emp_Addr[50];
            char Designation[50];
            char Phone_Num[20];
        } Employee_Type;
typedef enum {FAILURE,SUCCESS} status_code;
typedef enum {FALSE,TRUE} boolean;
typedef struct Key_Node_Tag
        {
            int Active_Keys;
            Key_Type Key_Arr[MAXKEYS + 1];
            void* Children[ARY + 1];
            struct Key_Node_Tag *parent;
            int Child_Type; /*0 -> Child is data node
                              1 -> Child is Key node*/
        } Key_Node;
typedef struct Data_Node_Tag
        {
            int Active_Data;
            Employee_Type Data_Arr[ARY + 1];
            Key_Node *parent;
            struct Data_Node_Tag *next;
            struct Data_Node_Tag *prev;       
        } Data_Node;
typedef struct BPlusTree_Tag
        {
            void* root;
            int root_type; /*0 -> Data node is root
                             1 -> Key node is root
                             -1 -> Root is NULL*/
            Data_Node *data_lptr;       
        } BPlusTree;

boolean GT(Key_Type K1,Key_Type K2);
boolean NEQ(Key_Type K1,Key_Type K2);
boolean LT(Key_Type K1,Key_Type K2);
void InitializeTree(BPlusTree *Tree_ptr);
status_code Insert(BPlusTree *Tree_ptr,Employee_Type Employee);
int Find_Data_Pos(Data_Node *dptr,Employee_Type Employee);
status_code Delete(BPlusTree *Tree_ptr,Employee_Type Employee);
void Search(BPlusTree *Tree_ptr,Key_Type E_Num);
int Height(BPlusTree *Tree_ptr);
int getNumRecords(BPlusTree *Tree_ptr);
void RangeSearch(BPlusTree *Tree_ptr,Key_Type Emp_Num1,Key_Type Emp_Num2);
Data_Node* Search_Data_Node(BPlusTree *Tree_ptr,Key_Type E_Num);
void PrintDatabase(BPlusTree *Tree_ptr);
boolean UpdateRecord(BPlusTree *Tree_ptr,Employee_Type Employee);
void read_From_File(BPlusTree *Tree_ptr,char fname[]);
void write_Into_File(BPlusTree *Tree_ptr,char fname[]);
void PrintStructure(Key_Node *kptr);
void Print_Tree(BPlusTree *Tree_ptr);

main()
{
    int i,choice,done;
    Key_Type E_Num,E_Num1,E_Num2;
    BPlusTree Tree;
    char E_Name[50],E_Desig[50],E_Addr[50],P_Num[20];
    status_code SC;
    Employee_Type Employee;
    InitializeTree(&Tree);
    printf("--------------------Welcome to the Employee Database--------------------\n\n");
    printf("Choose one of the following options:\n");
    printf("========================================================================\n");
    printf("                    1.Insert a record\n");
    printf("========================================================================\n");
    printf("                    2.Delete a record\n");
    printf("========================================================================\n");
    printf("                    3.Search for a record\n");
    printf("========================================================================\n");
    printf("                    4.Number of records in the database\n");
    printf("========================================================================\n");
    printf("                    5.Height of the B+ Tree\n");
    printf("========================================================================\n");
    printf("                    6.Range Search\n");
    printf("========================================================================\n");
    printf("                    7.Print Database\n");
    printf("========================================================================\n");
    done = 1;
    while(done == 1)
    {
        read_From_File(&Tree,"Employee_Database.txt");
        printf("Enter your choice:");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                 printf("Enter the record to be inserted/updated in the following order\n");
                 printf("Number\tName\tDesignation\tAddress\tPhone Number\n"); 
                 scanf("%d %s %s %s %s",&E_Num,E_Name,E_Desig,E_Addr,P_Num);
                 Employee.Emp_Num = E_Num;
                 strcpy(Employee.Emp_Name,E_Name);
                 strcpy(Employee.Designation,E_Desig);
                 strcpy(Employee.Emp_Addr,E_Addr);
                 strcpy(Employee.Phone_Num,P_Num);
                 SC = Insert(&Tree,Employee);
                 if(SC == 1)
                 {
                     printf("Insertion was successful!\n");      
                 }
                 else
                 {
                     printf("Insertion was unsuccessful!\n");    
                 }
                 break;
            case 2:
                 printf("Enter the Employee Number of the record to be deleted\n");
                 scanf("%d",&E_Num);
                 Employee.Emp_Num = E_Num;
                 strcpy(Employee.Emp_Name,"");
                 strcpy(Employee.Designation,"");
                 strcpy(Employee.Emp_Addr,"");
                 strcpy(Employee.Phone_Num,"");
                 SC = Delete(&Tree,Employee);
                 if(SC == 1)
                 {
                     printf("Deletion successful!\n");      
                 }
                 else
                 {
                     printf("Deletion unsuccessful!\n");    
                 }
                 break;
            case 3:
                 printf("Enter the Employee Number of the record to be searched\n");
                 scanf("%d",&E_Num);
                 Search(&Tree,E_Num);
                 break;
            case 4:
                 printf("The number of records in your database are %d\n",getNumRecords(&Tree));
                 break;
            case 5:
                 printf("The height of the B+ tree of your database is %d\n",Height(&Tree));
                 break;
            case 6:
                 printf("Enter the range in which the records are to be searched for\n");
                 scanf("%d %d",&E_Num1,&E_Num2);
                 RangeSearch(&Tree,E_Num1,E_Num2);
                 break;
            case 7:
                 PrintDatabase(&Tree);
                 break;
            default:
                 printf("You did not enter a valid option.Try again!\n");
                 break;                  
        }
        write_Into_File(&Tree,"Employee_Database.txt");
        printf("Enter one of the following options:\n");
        printf("1.Continue\n");
        printf("0.Exit\n");
        scanf("%d",&done);            
    }
    Print_Tree(&Tree);
    getch();      
}

void write_Into_File(BPlusTree *Tree_ptr,char fname[])
{
     FILE *fp;
     Data_Node *ptr;
     ptr = Tree_ptr -> data_lptr;
     int i;
     fp = fopen(fname,"w");
     while(ptr != NULL)
     {
         for(i = 0;i < ptr -> Active_Data;i++)
         {
             fprintf(fp,"%d %s %s %s %s\n",(ptr -> Data_Arr[i]).Emp_Num,(ptr -> Data_Arr[i]).Emp_Name,(ptr -> Data_Arr[i]).Designation,(ptr -> Data_Arr[i]).Emp_Addr,(ptr -> Data_Arr[i]).Phone_Num);
         }  
         ptr = ptr -> next;        
     }
     fclose(fp);
}

void read_From_File(BPlusTree *Tree_ptr,char fname[])
{
    FILE *fp;
    Key_Type E_Num;
    char E_Name[50],E_Desig[50],E_Addr[50],P_Num[20];
    Employee_Type Employee;
    status_code SC;
    InitializeTree(Tree_ptr);
    fp = fopen(fname,"r");
    while(!feof(fp))
    {
        fscanf(fp,"%d %s %s %s %s",&E_Num,E_Name,E_Desig,E_Addr,P_Num);
        Employee.Emp_Num = E_Num;
        strcpy(Employee.Emp_Name,E_Name);
        strcpy(Employee.Designation,E_Desig);
        strcpy(Employee.Emp_Addr,E_Addr);
        strcpy(Employee.Phone_Num,P_Num);
        SC = Insert(Tree_ptr,Employee);         
    }
    fclose(fp);     
}

void InitializeTree(BPlusTree *Tree_ptr)
{
    Tree_ptr -> root = NULL;
    Tree_ptr -> root_type = -1;
    Tree_ptr -> data_lptr = NULL;     
}

boolean LT(Key_Type K1,Key_Type K2)
{
    boolean ret_val;
    
    if(K1 < K2)
    {
        ret_val = TRUE;      
    }
    else
    {
        ret_val = FALSE;    
    }
    return ret_val;        
}

boolean GT(Key_Type K1,Key_Type K2)
{
    boolean ret_val;
    
    if(K1 > K2)
    {
        ret_val = TRUE;      
    }
    else
    {
        ret_val = FALSE;    
    }
    return ret_val;        
}

boolean NEQ(Key_Type K1,Key_Type K2)
{
    boolean ret_val;
    
    if(K1 != K2)
    {
        ret_val = TRUE;      
    }
    else
    {
        ret_val = FALSE;    
    }
    return ret_val;        
}

boolean UpdateRecord(BPlusTree *Tree_ptr,Employee_Type Employee)
{
    boolean ret_val;
    Data_Node *d_ptr;
    int pos;
    if(Tree_ptr -> root == NULL)
    {
        ret_val = FALSE;            
    }
    else
    {
        d_ptr = Search_Data_Node(Tree_ptr,Employee.Emp_Num);
        pos = Find_Data_Pos(d_ptr,Employee);
        if(pos != -1)
        {
            d_ptr -> Data_Arr[pos] = Employee;
            ret_val = TRUE;       
        }
        else
        {
            ret_val = FALSE;    
        }    
    }
    return ret_val;        
}

status_code Insert(BPlusTree *Tree_ptr,Employee_Type Employee)
{
    status_code SC = SUCCESS;
    Data_Node *data_ptr,*d,*new_data,*current_data;
    Key_Node *key_ptr,*parent_ptr,*current_ptr,*new_ptr;
    Key_Type new_Key;
    int i,pos,done;
    boolean Updated;
    Updated = UpdateRecord(Tree_ptr,Employee);
    if(Updated)
    {
        SC = SUCCESS;       
    }
    else if(Tree_ptr -> root == NULL)/*Root is NULL*/
    {
        data_ptr = (Data_Node*)malloc(sizeof(Data_Node));
        if(data_ptr == NULL)
        {
            SC = FAILURE;            
        }
        else
        {
            data_ptr -> Data_Arr[0] = Employee;
            data_ptr -> Active_Data = 1;
            data_ptr -> parent = NULL;
            data_ptr -> next = NULL;
            data_ptr -> prev = NULL;
            
            Tree_ptr -> root = data_ptr;
            Tree_ptr -> root_type = 0;
            Tree_ptr -> data_lptr = data_ptr;    
        }
    }
    else if(Tree_ptr -> root_type == 0)/*Root is a data node*/
    {
        data_ptr = (Data_Node*)(Tree_ptr -> root);
        data_ptr -> Data_Arr[data_ptr -> Active_Data] = Employee;
        i = data_ptr -> Active_Data - 1;
        //Sort the data node-Insertion sort
        while((i >= 0) && (LT(Employee.Emp_Num,(data_ptr -> Data_Arr[i]).Emp_Num)))
        {
            data_ptr -> Data_Arr[i + 1] = data_ptr -> Data_Arr[i];
            data_ptr -> Data_Arr[i] = Employee;
            i--;         
        }
        if(data_ptr -> Active_Data < MAXKEYS + 1)//Capacity has not exceeded
        {
            data_ptr -> Active_Data = data_ptr -> Active_Data + 1;            
        }
        else
        {
            //Make a new data node
            new_data = (Data_Node*)malloc(sizeof(Data_Node));
            //Make a new key node
            key_ptr = (Key_Node*)malloc(sizeof(Key_Node));
            if(new_data == NULL || key_ptr == NULL)
            {
                SC = FAILURE;            
            }
            else
            {
                //Set the doubly linked list pointers
                current_data = data_ptr;
                current_data -> next = new_data;
                new_data -> prev = current_data;
                new_data -> next = NULL;
                
                if(ARY%2 == 1)
                {
                    //Insert data into the new data node from the one which has become full
                    for(i = 0;i < MINKEYS + 1;i++)
                    {
                        new_data -> Data_Arr[i] = current_data -> Data_Arr[MINKEYS + 1 + i];      
                    }
                
                    current_data -> Active_Data = MINKEYS + 1;
                    new_data -> Active_Data = MINKEYS + 1;
                }
                else
                {
                    (current_data -> Active_Data)++;
                    new_data -> Active_Data = 0;
                    for(i = 0;i < ARY/2;i++)
                    {
                        new_data -> Data_Arr[i] = current_data -> Data_Arr[ARY/2 + 1 + i];
                        (current_data -> Active_Data)--;
                        (new_data -> Active_Data)++;      
                    }    
                }
                //Insert the key in the key node
                key_ptr -> Key_Arr[0] = (new_data -> Data_Arr[0]).Emp_Num;
                key_ptr -> Active_Keys = 1;
                key_ptr -> Children[0] = current_data;
                key_ptr -> Children[1] = new_data;
                key_ptr -> Child_Type = 0;
                key_ptr -> parent = NULL;
                
                //Link the data node with the key node --> Parent - Child relation
                current_data -> parent = key_ptr;
                new_data -> parent = key_ptr;
                
                //Change the root
                Tree_ptr -> root = key_ptr;
                Tree_ptr -> root_type = 1;
            }
        }
    }
    else
    {
        //Assign the root to a key node
        key_ptr = (Key_Node*)Tree_ptr -> root;
        //Traverse to the level which contains the key nodes having data nodes as their children
        while(key_ptr -> Child_Type == 1)
        {
            pos = Find_Branch(key_ptr,Employee.Emp_Num);
            key_ptr = key_ptr -> Children[pos];              
        }
        //Find the branch of the data node corresponding to the new Key of the data to be inserted
        pos = Find_Branch(key_ptr,Employee.Emp_Num);
        data_ptr = key_ptr -> Children[pos];
        
        //Insert the data and sort it on key-Insertion sort
        data_ptr -> Data_Arr[data_ptr -> Active_Data] = Employee;
        i = data_ptr -> Active_Data - 1;
        while((i >= 0) && (LT(Employee.Emp_Num,(data_ptr -> Data_Arr[i]).Emp_Num)))
        {
            data_ptr -> Data_Arr[i + 1] = data_ptr -> Data_Arr[i];
            data_ptr -> Data_Arr[i] = Employee;
            i--;         
        }
        if(data_ptr -> Active_Data < MAXKEYS + 1)//If the data node is not full
        {
            //Increment the number of active elements
            data_ptr -> Active_Data = data_ptr -> Active_Data + 1;            
        }
        else
        {
            //Data node is full so we need to split it now
            new_data = (Data_Node*)malloc(sizeof(Data_Node));
            if(new_data == NULL)
            {
                SC = FAILURE;            
            }
            else
            {
                //Set the doubly linked list pointers
                current_data = data_ptr;
                new_data -> next = current_data -> next;
                current_data -> next = new_data;
                new_data -> prev = current_data;
                if(new_data -> next != NULL)
                {
                    (new_data -> next) -> prev = new_data;
                }
                
                if(ARY%2 ==1)
                {
                    //Insert data into the new data node from the one which is full
                    for(i = 0;i < MINKEYS + 1;i++)
                    {
                        new_data -> Data_Arr[i] = current_data -> Data_Arr[MINKEYS + 1 + i];      
                    }
                
                    current_data -> Active_Data = MINKEYS + 1;
                    new_data -> Active_Data = MINKEYS + 1;
                }
                else
                {
                    (current_data -> Active_Data)++;
                    new_data -> Active_Data = 0;
                    for(i = 0;i < ARY/2;i++)
                    {
                        new_data -> Data_Arr[i] = current_data -> Data_Arr[ARY/2 + 1 + i];
                        (current_data -> Active_Data)--;
                        (new_data -> Active_Data)++;      
                    }    
                }
                //The key to be inserted into the key node
                new_Key = (new_data -> Data_Arr[0]).Emp_Num;
                key_ptr -> Key_Arr[key_ptr -> Active_Keys] = new_Key;
                key_ptr -> Children[key_ptr -> Active_Keys + 1] = new_data;
                i = key_ptr -> Active_Keys - 1;
                //Insert the data node and the new key into its proper sorted place
                while((i >= 0) && LT(new_Key,key_ptr -> Key_Arr[i]))
                {
                    key_ptr -> Key_Arr[i + 1] = key_ptr -> Key_Arr[i];
                    key_ptr -> Children[i + 2] = key_ptr -> Children[i + 1];
                    key_ptr -> Key_Arr[i] = new_Key;
                    key_ptr -> Children[i + 1] = new_data;
                    i--;         
                }
                //Create the parent link of the new data node
                new_data -> parent = key_ptr;
                if(key_ptr -> Active_Keys < MAXKEYS)//Key node is not full yet
                {
                    //Increment the number of active keys
                    key_ptr -> Active_Keys = key_ptr -> Active_Keys + 1;           
                }
                else
                {
                    //The key node is full and now it needs to be split
                    new_ptr = (Key_Node*)malloc(sizeof(Key_Node));
                    if(new_ptr == NULL)
                    {
                        SC =  FAILURE;           
                    }    
                    else
                    {
                        current_ptr = key_ptr;
                        if(ARY%2 == 1)
                        {
                            //Insert keys into the new key node from the one which is full
                            for(i = 0;i < MINKEYS;i++)
                            {
                                new_ptr -> Key_Arr[i] = current_ptr -> Key_Arr[MINKEYS + 1 + i];       
                            }
                        
                            //Insert the appropriate children
                            for(i = 0;i <= MINKEYS;i++)
                            {
                                new_ptr -> Children[i] = current_ptr -> Children[MINKEYS + 1 + i];
                                ((Data_Node*)(new_ptr -> Children[i])) -> parent = new_ptr;
                            }
                        
                            //Change the number of active keys
                            current_ptr -> Active_Keys = MINKEYS;
                            new_ptr -> Active_Keys = MINKEYS;
                            new_ptr -> Child_Type = current_ptr -> Child_Type;
                            new_ptr -> parent = current_ptr -> parent;
                        
                            //Key to be inserted into a higher node
                            new_Key = current_ptr -> Key_Arr[MINKEYS];
                        }
                        else
                        {
                            new_ptr -> Active_Keys = 0;
                            for(i = 0;i < ARY/2 - 1;i++)
                            {
                                new_ptr -> Key_Arr[i] = current_ptr -> Key_Arr[ARY/2 + 1 + i];
                                (current_ptr -> Active_Keys)--;
                                (new_ptr -> Active_Keys)++;       
                            }
                            
                             for(i = 0;i <= ARY/2 - 1;i++)
                            {
                                new_ptr -> Children[i] = current_ptr -> Children[ARY/2 + 1 + i];
                                ((Data_Node*)(new_ptr -> Children[i])) -> parent = new_ptr;
                            }
                            
                            new_ptr -> Child_Type = current_ptr -> Child_Type;
                            new_ptr -> parent = current_ptr -> parent;
                            new_Key = current_ptr -> Key_Arr[ARY/2];    
                        }
                        done = 0;
                        while(!done)
                        {
                            //If the key node which has split was the root
                            if(current_ptr -> parent == NULL)
                            {
                                //Make a new key node
                                key_ptr = (Key_Node*)malloc(sizeof(Key_Node));
                                if(key_ptr == NULL)
                                {
                                    SC = FAILURE;           
                                }
                                else
                                {
                                    //Assign the key and children
                                    key_ptr -> parent = NULL;
                                    key_ptr -> Key_Arr[0] = new_Key;
                                    key_ptr -> Active_Keys = 1;
                                    key_ptr -> Children[0] = current_ptr;
                                    key_ptr -> Children[1] = new_ptr;
                                    key_ptr -> Child_Type = 1;
                                    
                                    //Change the root
                                    Tree_ptr -> root = key_ptr;
                                    Tree_ptr -> root_type = 1;
                                    done = 1;
                                    
                                    //Link the parent-child relation
                                    current_ptr -> parent = key_ptr;
                                    new_ptr -> parent = key_ptr;    
                                }               
                            }
                            else
                            {
                                //Parent exists
                                parent_ptr = current_ptr -> parent;
                                //Insert the new key and child
                                parent_ptr -> Key_Arr[parent_ptr -> Active_Keys] = new_Key;
                                parent_ptr -> Children[parent_ptr -> Active_Keys + 1] = new_ptr;
                                i = parent_ptr -> Active_Keys - 1;
                                //Sort both the child and key
                                while((i >= 0) && LT(new_Key,parent_ptr -> Key_Arr[i]))
                                {
                                    parent_ptr -> Key_Arr[i + 1] = parent_ptr -> Key_Arr[i];
                                    parent_ptr -> Children[i + 2] = parent_ptr -> Children[i + 1];
                                    parent_ptr -> Key_Arr[i] = new_Key;
                                    parent_ptr -> Children[i + 1] = new_ptr;
                                    i--;
                                }
                                //Establish the parent link         
                                new_ptr -> parent = parent_ptr;
                                //The parent key node is not yet full
                                if(parent_ptr -> Active_Keys < MAXKEYS)
                                {
                                    //Increment the number of active keys and we are done
                                    parent_ptr -> Active_Keys = parent_ptr -> Active_Keys + 1;
                                    done = 1;           
                                }
                                else
                                {
                                    //The key node has to be split
                                    new_ptr = (Key_Node*)malloc(sizeof(Key_Node));
                                    if(new_ptr == NULL)
                                    {
                                        SC = FAILURE;           
                                    }
                                    else
                                    {
                                        current_ptr = parent_ptr;
                                        if(ARY%2 == 1)
                                        {
                                            //Insert the keys into the new key node from the key node which was full
                                            for(i = 0;i < MINKEYS;i++)
                                            {
                                                new_ptr -> Key_Arr[i] = current_ptr -> Key_Arr[MINKEYS + i + 1];       
                                            }
                                            //Insert the corresponding children too
                                            for(i = 0;i <= MINKEYS;i++)
                                            {
                                                new_ptr -> Children[i] = current_ptr -> Children[MINKEYS + 1 + i];
                                                ((Key_Node*)(new_ptr -> Children[i])) -> parent = new_ptr;
                                            }
                                        
                                            current_ptr -> Active_Keys = MINKEYS;
                                            new_ptr -> Active_Keys = MINKEYS;
                                            new_ptr -> Child_Type = current_ptr -> Child_Type;
                                            new_ptr -> parent = current_ptr -> parent;
                                        
                                            new_Key = current_ptr -> Key_Arr[MINKEYS];
                                        }
                                        else
                                        {
                                            new_ptr -> Active_Keys = 0;
                                            for(i = 0;i < ARY/2 - 1;i++)
                                            {
                                                new_ptr -> Key_Arr[i] = current_ptr -> Key_Arr[ARY/2 + 1 + i];
                                                (current_ptr -> Active_Keys)--;
                                                (new_ptr -> Active_Keys)++;       
                                            }
                            
                                            for(i = 0;i <= ARY/2 - 1;i++)
                                            {               
                                                new_ptr -> Children[i] = current_ptr -> Children[ARY/2 + 1 + i];
                                                ((Key_Node*)(new_ptr -> Children[i])) -> parent = new_ptr;
                                            }
                            
                                            new_ptr -> Child_Type = current_ptr -> Child_Type;
                                            new_ptr -> parent = current_ptr -> parent;
                                            new_Key = current_ptr -> Key_Arr[ARY/2];    
                                        }     
                                    }       
                                }
                            }            
                        }          
                    }
                }
                   
            }    
        }
    }
    return SC;            
}

int Find_Branch(Key_Node *key_ptr,Key_Type k)
{
    int i;
    i = 0;
    while(GT(k,key_ptr -> Key_Arr[i]) && i < key_ptr -> Active_Keys)
    {
        i++;                   
    }
    if(!NEQ(k,key_ptr -> Key_Arr[i]) && (i != key_ptr -> Active_Keys))
    {
        i++;                  
    }
    return i;    
}

status_code Delete(BPlusTree *Tree_ptr,Employee_Type Employee)
{
    status_code SC = SUCCESS;
    Key_Node *key_ptr,*parent_kptr,*left_kptr,*right_kptr;
    Data_Node *data_ptr,*left_dptr,*right_dptr;
    int i,done,pos;
    done = 1;
    //If the tree is empty then we can't delete anything
    if(Tree_ptr -> root == NULL)
    {
        SC =  FAILURE;
        done = 1;            
    }
    else if(Tree_ptr -> root_type == 0)
    {
         //If the root is a data node
        data_ptr = (Data_Node*)(Tree_ptr -> root);
        //Find the position of the element to be deleted inside the data node
        pos = Find_Data_Pos(data_ptr,Employee);
        if(pos != -1)
        {
            //Element exists
            //Delete the element --> Shift the elements after 'pos' one position left   
            for(i = pos;i < data_ptr -> Active_Data - 1;i++)
            {
                data_ptr -> Data_Arr[i] = data_ptr -> Data_Arr[i + 1];      
            }
            //Decrease the number of active data
            data_ptr -> Active_Data = data_ptr -> Active_Data - 1;
            if(data_ptr -> Active_Data == 0)
            {
                //If no elements are remaining in our data node,then the tree has become empty
                free(data_ptr);
                data_ptr = NULL;
            
                Tree_ptr -> root = NULL;
                Tree_ptr -> root_type = -1;
                Tree_ptr -> data_lptr = NULL;            
            }
        }
        else
        {
            //Element to be deleted is not found in the data node -> Error conditiom
            SC = FAILURE;
        }
        done = 1;          
    }
    else
    {
        //Root is a key node
        key_ptr = (Key_Node*)(Tree_ptr -> root);
        
        //Traverse to the keynode which is the parent of the data node which contains the element to be deleted
        while(key_ptr -> Child_Type == 1)
        {
            pos = Find_Branch(key_ptr,Employee.Emp_Num);
            key_ptr = key_ptr -> Children[pos];              
        }
        //Traverse to the data node which contains the element to be deleted
        pos = Find_Branch(key_ptr,Employee.Emp_Num);
        data_ptr = key_ptr -> Children[pos];
        
        //Find the posision of the element to be deleted in the data node
        pos = Find_Data_Pos(data_ptr,Employee);
        if(pos == -1)
        {
            //If element is not found then it is a failure condition
            SC = FAILURE;       
        }
        else
        {
            //Element is found
            //Delete the element --> Shift the elements after 'pos' one position left 
            for(i = pos;i < data_ptr -> Active_Data - 1;i++)
            {
                data_ptr -> Data_Arr[i] = data_ptr -> Data_Arr[i + 1];      
            }
            if(data_ptr -> Active_Data > MINKEYS + 1)//Check if data node contains minimun number of required elements after deletion
            {
                data_ptr -> Active_Data = data_ptr -> Active_Data - 1;
            }
            else
            {
                //Data node contains less than the minimum number of elements required hence has to be merged with a sibling 
                //Find the parent of the data node
                key_ptr = data_ptr -> parent;
                
                //Immediate right and left data nodes --> To check is they are siblings of the data node
                right_dptr = data_ptr -> next;
                left_dptr = data_ptr -> prev;
                if(right_dptr != NULL)
                {
                    //If the immediate right node is not a sibling,then make it NULL
                    if(right_dptr -> parent != key_ptr)
                    {
                        right_dptr = NULL;
                    }              
                }

                if(left_dptr != NULL)
                {
                    //If the immediate left node is not a sibling,then make it NULL
                    if(left_dptr -> parent != key_ptr)
                    {
                        left_dptr = NULL;             
                    }             
                }
                //If right sibling exists and it can give an element to the deficient node
                if(right_dptr != NULL && right_dptr -> Active_Data > MINKEYS + 1)
                {
                    //Take the element from the right sibling
                    data_ptr -> Data_Arr[data_ptr -> Active_Data - 1] = right_dptr -> Data_Arr[0];
                    //Sort the rest elements of the right sibling    
                    for(i = 0;i < right_dptr -> Active_Data - 1;i++)
                    {
                        right_dptr -> Data_Arr[i] = right_dptr -> Data_Arr[i + 1];      
                    }
                    //Decrement the number of active data in right sibling    
                    right_dptr -> Active_Data = right_dptr -> Active_Data - 1;
                    //Find the in-between key in the Key node    
                    pos = Find_Branch(key_ptr,(right_dptr -> Data_Arr[0]).Emp_Num);
                    //Change the corresponding key in the Key node
                    key_ptr -> Key_Arr[pos - 1] = (right_dptr -> Data_Arr[0]).Emp_Num;
                        
                    data_ptr -> Active_Data = MINKEYS + 1;
                    done = 1;              
                }
                else if((left_dptr != NULL) && ((left_dptr -> Active_Data) > MINKEYS + 1))
                {
                    //If left sibling exists and it can give an element to the deficient node
                    //Make room in the deficient node for the new element to be lent     
                    for(i = data_ptr -> Active_Data - 1;i > 0;i--)
                    {
                        data_ptr -> Data_Arr[i] = data_ptr -> Data_Arr[i - 1];      
                    }
                    //Lend the element    
                    data_ptr -> Data_Arr[0] = left_dptr -> Data_Arr[left_dptr -> Active_Data - 1];
                    //Decrement the number of active data in the left sibling    
                    left_dptr -> Active_Data = left_dptr -> Active_Data - 1;
                    //Find the in-between key in the Key Node    
                    pos = Find_Branch(key_ptr,(data_ptr -> Data_Arr[1]).Emp_Num);
                    //Set the new key
                    key_ptr -> Key_Arr[pos - 1] = (data_ptr -> Data_Arr[0]).Emp_Num;
                        
                    data_ptr -> Active_Data = MINKEYS + 1;
                    done = 1;     
                }
                else
                {
                    //We cannot lend elements from siblings hence we have to merge the siblings which are available
                    if(right_dptr != NULL)
                    {
                        //If right sibling exists,merge the nodes
                        for(i = 0;i < right_dptr -> Active_Data;i++)
                        {
                            data_ptr -> Data_Arr[data_ptr -> Active_Data - 1 + i] = right_dptr -> Data_Arr[i];      
                        }
                        //Set the links of the doubly linked list
                        data_ptr -> next = right_dptr -> next;
                        if(right_dptr -> next != NULL)
                        {
                            (right_dptr -> next) -> prev = data_ptr;             
                        }
                        //Set the number of active data
                        data_ptr -> Active_Data = data_ptr -> Active_Data + right_dptr -> Active_Data - 1;
                        free(right_dptr);
                        right_dptr = NULL;
                        //We have to delete the in-between key,so find it's position
                        pos = Find_Branch(key_ptr,(data_ptr -> Data_Arr[0]).Emp_Num);
                        //Delete the key
                        for(i = pos;i < key_ptr -> Active_Keys - 1;i++)
                        {
                            key_ptr -> Key_Arr[i] = key_ptr -> Key_Arr[i + 1];
                            key_ptr -> Children[i + 1] = key_ptr -> Children[i + 2];      
                        }
                        
                        if(key_ptr -> Active_Keys > MINKEYS)//If the key node does not become deficient after deletion
                        {
                            key_ptr -> Active_Keys = key_ptr -> Active_Keys - 1;
                            done = 1;           
                        }
                        else if(key_ptr -> parent == NULL)//If the key node is a root
                        {
                            key_ptr -> Active_Keys = key_ptr -> Active_Keys - 1;
                            
                            if(key_ptr -> Active_Keys == 0)
                            {
                                //Key node becomes empty -> Only data node remaining hence data node should become the root
                                free(key_ptr);
                                key_ptr = NULL;
                                data_ptr -> parent = NULL;
                                
                                Tree_ptr -> root = data_ptr;
                                Tree_ptr -> root_type = 0;           
                            }
                            done = 1;     
                        }
                        else
                        {
                            //Key node has to be handled separately now
                            done = 0;
                        }              
                    }
                    else if(left_dptr != NULL)
                    {
                        //Left sibling of data node exists
                        //Decrease the number of active elements in our data node
                        data_ptr -> Active_Data = data_ptr -> Active_Data - 1;
                        //Bring the elements from our deficient node to the left sibling
                        for(i = 0;i < data_ptr -> Active_Data;i++)
                        {
                            left_dptr -> Data_Arr[left_dptr -> Active_Data + i] = data_ptr -> Data_Arr[i];      
                        }
                        
                        left_dptr -> Active_Data = (left_dptr -> Active_Data) + (data_ptr -> Active_Data);
                        //Handle the doubly linked list
                        left_dptr -> next = data_ptr -> next;
                        if(data_ptr -> next != NULL)
                        {
                            (data_ptr -> next) -> prev = left_dptr;            
                        }
                        free(data_ptr);
                        data_ptr = NULL;
                        
                        //We have to delete the in-between key,so find it's position
                        pos = Find_Branch(key_ptr,(left_dptr -> Data_Arr[0]).Emp_Num);
                        //Delete the key
                        for(i = pos;i < key_ptr -> Active_Keys - 1;i++)
                        {
                            key_ptr -> Key_Arr[i] = key_ptr -> Key_Arr[i + 1];
                            key_ptr -> Children[i + 1] = key_ptr -> Children[i + 2];      
                        }
                        if(key_ptr -> Active_Keys > MINKEYS)//If the key node does not become deficient after deletion
                        {
                            key_ptr -> Active_Keys = key_ptr -> Active_Keys - 1;
                            done = 1;           
                        }
                        else if(key_ptr -> parent == NULL)//If the key node is a root
                        {
                            key_ptr -> Active_Keys = key_ptr -> Active_Keys - 1;
                            
                            if(key_ptr -> Active_Keys == 0)
                            {
                                //Key node becomes empty -> Only data node remaining hence data node should become the root
                                free(key_ptr);
                                key_ptr = NULL;
                                left_dptr -> parent = NULL;
                                
                                Tree_ptr -> root = left_dptr;
                                Tree_ptr -> root_type = 0;           
                            }
                            done = 1;     
                        }
                        else
                        {
                            //Key node has to be handled separately now
                            done = 0;
                        }    
                    }    
                }                
            }    
        }        
    }
    while(!done)
    {
        //Decrement the number of active keys and find the parent
        key_ptr -> Active_Keys = key_ptr -> Active_Keys - 1;
        parent_kptr = key_ptr -> parent;
        //Find the branch of the parent we are in
        pos = Find_Branch(parent_kptr,key_ptr -> Key_Arr[0]);
        if(pos == 0)
        {
            //Left sibling of key node does not exist
            left_kptr = NULL;       
        }
        else
        {
            left_kptr = parent_kptr -> Children[pos - 1];    
        }
        if(pos >= parent_kptr -> Active_Keys)
        {
            //Right sibling of key node does not exist
            right_kptr = NULL;       
        }
        else
        {
            right_kptr = parent_kptr -> Children[pos + 1];    
        }
        //If left sibling of key node exists and it can give a key
        if(left_kptr != NULL && left_kptr -> Active_Keys > MINKEYS)
        {
            //Shift All the elements of the key node one position right
            for(i = key_ptr -> Active_Keys;i > 0;i--)
            {
                key_ptr -> Key_Arr[i] = key_ptr -> Key_Arr[i - 1];      
            }
            //Shift the children to make room for the new child
            for(i = key_ptr -> Active_Keys + 1;i > 0;i--)
            {
                key_ptr -> Children[i] = key_ptr -> Children[i - 1];      
            }
            //Find the position of the in-between key
            pos = Find_Branch(parent_kptr,left_kptr -> Key_Arr[0]);
            //Lend the key from the parent
            key_ptr -> Key_Arr[0] = parent_kptr -> Key_Arr[pos];
            //Lend the child from the left sibling
            key_ptr -> Children[0] = left_kptr -> Children[left_kptr -> Active_Keys];
            //Establish the parent links
            if(key_ptr -> Child_Type == 0)
            {
                ((Data_Node*)(key_ptr -> Children[0])) -> parent = key_ptr;
            }
            else
            {
                ((Key_Node*)(key_ptr -> Children[0])) -> parent = key_ptr;
            }
            //Left sibling gives a key to the parent
            parent_kptr -> Key_Arr[pos] = left_kptr -> Key_Arr[left_kptr -> Active_Keys - 1];
            //Decrement the number of active keys in the left sibling
            left_kptr -> Active_Keys = left_kptr -> Active_Keys - 1;
            //Increase the number of active keys in my key node
            key_ptr -> Active_Keys = key_ptr -> Active_Keys + 1;
            //We are done
            done = 1;                     
        }
        else if(right_kptr != NULL && right_kptr -> Active_Keys > MINKEYS)
        {
            //If right sibling of key node exists and it can give a key
            //Find the position of the in-between key in the parent node 
            pos = Find_Branch(parent_kptr,key_ptr -> Key_Arr[0]);
            //Lend the key from the parent
            key_ptr -> Key_Arr[key_ptr -> Active_Keys] = parent_kptr -> Key_Arr[pos];
            //Lend a child from the right sibling
            key_ptr -> Children[key_ptr -> Active_Keys + 1] = right_kptr -> Children[0];
            //Establish the parent links
            if(key_ptr -> Child_Type == 0)
            {
                ((Data_Node*)key_ptr -> Children[key_ptr -> Active_Keys + 1]) -> parent = key_ptr;
            }
            else
            {
                ((Key_Node*)key_ptr -> Children[key_ptr -> Active_Keys + 1]) -> parent = key_ptr;
            }
            key_ptr -> Active_Keys = key_ptr -> Active_Keys + 1;
                                
            //Right sibling gives a key to the parent
            parent_kptr -> Key_Arr[pos] = right_kptr -> Key_Arr[0];
            //Left shift all the keys and children in the right sibling
            for(i = 0;i < right_kptr -> Active_Keys - 1;i++)
            {
                right_kptr -> Key_Arr[i] = right_kptr -> Key_Arr[i + 1];      
            }
            for(i = 0;i < right_kptr -> Active_Keys;i++)
            {
                right_kptr -> Children[i] = right_kptr -> Children[i + 1];      
            }
            //Decrement the number of active keys in the right sibling
            right_kptr -> Active_Keys = right_kptr -> Active_Keys - 1;
            //We are done 
            done = 1; 
        }
        else
        {
            //Now we have to merge the key nodes because we cannot lend the key from any sibling
            if(left_kptr != NULL)
            {
                //Find the position of the in-between key in the parent node
                pos = Find_Branch(parent_kptr,left_kptr -> Key_Arr[0]);
                //Bring the in-between key down
                left_kptr -> Key_Arr[left_kptr -> Active_Keys] = parent_kptr -> Key_Arr[pos];
                left_kptr -> Active_Keys = left_kptr -> Active_Keys + 1;
                //Bring the keys from the deficient node
                for(i = 0;i < key_ptr -> Active_Keys;i++)
                {
                    left_kptr -> Key_Arr[left_kptr -> Active_Keys + i] = key_ptr -> Key_Arr[i];         
                }
                //Bring the children from the deficient node
                for(i = 0;i <= key_ptr -> Active_Keys;i++)
                {
                    left_kptr -> Children[left_kptr -> Active_Keys + i] = key_ptr -> Children[i];
                    if(key_ptr -> Child_Type == 0)
                    {
                        ((Data_Node*)(left_kptr -> Children[left_kptr -> Active_Keys + i])) -> parent = left_kptr;              
                    } 
                    else
                    {
                        ((Key_Node*)(left_kptr -> Children[left_kptr -> Active_Keys + i])) -> parent = left_kptr;
                    }     
                }
                left_kptr -> Active_Keys = (left_kptr -> Active_Keys) + (key_ptr -> Active_Keys);
                free(key_ptr);
                key_ptr = NULL;
                //Sort the parent node
                for(i = pos;i < parent_kptr -> Active_Keys - 1;i++)
                {
                    parent_kptr -> Key_Arr[i] = parent_kptr -> Key_Arr[i + 1];          
                }
                for(i = pos + 1;i < parent_kptr -> Active_Keys;i++)
                {
                    parent_kptr -> Children[i] = parent_kptr -> Children[i + 1];          
                }
                                        
                if(parent_kptr -> Active_Keys > MINKEYS)
                {
                    //Parent is not deficient
                    parent_kptr -> Active_Keys = parent_kptr -> Active_Keys - 1;
                    done = 1;               
                }
                else
                {
                    if(parent_kptr -> parent == NULL)
                    {
                        //Parent is a root
                        //No restriction on root so decrement the number of active keys
                        parent_kptr -> Active_Keys = parent_kptr -> Active_Keys - 1;
                        if(parent_kptr -> Active_Keys != 0)
                        {
                            done = 1;               
                        }
                        else
                        {
                            //If the number of keys in the root becomes zero change the root
                            free(parent_kptr);
                            parent_kptr = NULL;
                                                    
                            left_kptr -> parent = NULL;
                                                    
                            Tree_ptr -> root = left_kptr;
                            Tree_ptr -> root_type = 1;
                            done = 1;
                        }                   
                    }
                    else
                    {
                        //Parent is deficient now,so we have to enter the loop again
                        key_ptr = parent_kptr;     
                    }    
                }             
            }
            else if(right_kptr != NULL)
            {
                //Right sibling exists -- We have to merge it with our deficient key node
                //Find the position of the in-between element
                pos = Find_Branch(parent_kptr,key_ptr -> Key_Arr[0]);
                //Lend a key from the parent
                key_ptr -> Key_Arr[key_ptr -> Active_Keys] = parent_kptr -> Key_Arr[pos];
                //Increment the number of active keys
                key_ptr -> Active_Keys = key_ptr -> Active_Keys + 1;
                //Bring all keys from the right sibling
                for(i = 0;i < right_kptr -> Active_Keys;i++)
                {
                    key_ptr -> Key_Arr[key_ptr -> Active_Keys + i] = right_kptr -> Key_Arr[i];   
                }
                   
                //Bring all the children from the right sibling
                for(i = 0;i <= right_kptr -> Active_Keys;i++)
                {
                    key_ptr -> Children[key_ptr -> Active_Keys + i] = right_kptr -> Children[i];
                    if(key_ptr -> Child_Type == 0)
                    {
                        ((Data_Node*)(key_ptr -> Children[key_ptr -> Active_Keys + i])) -> parent = key_ptr;           
                    }
                    else
                    {
                        ((Key_Node*)(key_ptr -> Children[key_ptr -> Active_Keys + i])) -> parent = key_ptr;
                    }      
                }
                //Increment the number of active keys in the deficient node
                key_ptr -> Active_Keys = (key_ptr -> Active_Keys) + (right_kptr -> Active_Keys);
                free(right_kptr);
                right_kptr = NULL;
                //Sort the rest of the keys and children in the parent node
                for(i = pos;i < parent_kptr -> Active_Keys - 1;i++)
                {
                    parent_kptr -> Key_Arr[i] = parent_kptr -> Key_Arr[i + 1];      
                }
                for(i = pos + 1;i < parent_kptr -> Active_Keys;i++)
                {
                    parent_kptr -> Children[i] = parent_kptr -> Children[i + 1];      
                }
                if(parent_kptr -> Active_Keys > MINKEYS)
                {
                    //If parent is not deficient we are done
                    parent_kptr -> Active_Keys = parent_kptr -> Active_Keys - 1;
                    done = 1;               
                }
                else
                {
                    if(parent_kptr -> parent == NULL)
                    {
                        //Parent is a root
                        //No restriction on root hence decrement the number of active keys
                        parent_kptr -> Active_Keys = parent_kptr -> Active_Keys - 1;
                        if(parent_kptr -> Active_Keys != 0)
                        {
                            done = 1;               
                        }
                        else
                        {
                            //If number of active keys becomes zero,change the root
                            free(parent_kptr);
                            parent_kptr = NULL;
                                                    
                            key_ptr -> parent = NULL;
                                                    
                            Tree_ptr -> root = key_ptr;
                            Tree_ptr -> root_type = 1;
                            done = 1;    
                        }                   
                    }
                    else
                    {
                        //Repeat the same procedure for the deficient parent
                        key_ptr = parent_kptr;     
                    }
                }       
            }    
        }
    }
    return SC;            
}

int Find_Data_Pos(Data_Node *dptr,Employee_Type Employee)
{
    Key_Type k;
    int i;
    k = Employee.Emp_Num;
    i = 0;
    while((i < dptr -> Active_Data) && NEQ(k,(dptr -> Data_Arr[i]).Emp_Num))
    {
        i++;         
    }
    if(i == dptr -> Active_Data)
    {
        i = -1;     
    }
    return i;    
}

void Search(BPlusTree *Tree_ptr,Key_Type E_Num)
{
    int pos;
    Key_Node *k_ptr;
    Data_Node *d_ptr;
    Employee_Type Employee;
    
    if(Tree_ptr -> root == NULL)
    {
        pos = -1;
        d_ptr = NULL;            
    }
    else if(Tree_ptr -> root_type == 0)
    {
        d_ptr = (Data_Node*)(Tree_ptr -> root);
        Employee.Emp_Num = E_Num;
        pos = Find_Data_Pos(d_ptr,Employee);
        if(pos != -1)
        {
            printf("%d %s %s %s %s\n",(d_ptr -> Data_Arr[pos]).Emp_Num,(d_ptr -> Data_Arr[pos]).Emp_Name,(d_ptr -> Data_Arr[pos]).Designation,(d_ptr -> Data_Arr[pos]).Emp_Addr,(d_ptr -> Data_Arr[pos]).Phone_Num);      
        }
        else
        {
            printf("Your database does not contain the record you are searching for\n");    
        }     
    }
    else
    {
        k_ptr = (Key_Node*)(Tree_ptr -> root);
        while(k_ptr -> Child_Type == 1)
        {
            pos = Find_Branch(k_ptr,E_Num);
            k_ptr = k_ptr -> Children[pos];            
        }
        pos = Find_Branch(k_ptr,E_Num);
        d_ptr = k_ptr -> Children[pos];
        
        Employee.Emp_Num = E_Num;
        pos = Find_Data_Pos(d_ptr,Employee);
        if(pos != -1)
        {
            printf("%d %s %s %s %s\n",(d_ptr -> Data_Arr[pos]).Emp_Num,(d_ptr -> Data_Arr[pos]).Emp_Name,(d_ptr -> Data_Arr[pos]).Designation,(d_ptr -> Data_Arr[pos]).Emp_Addr,(d_ptr -> Data_Arr[pos]).Phone_Num);       
        }
        else
        {
            printf("Your database does not contain the record you are searching for\n");   
        }    
    }    
}

Data_Node* Search_Data_Node(BPlusTree *Tree_ptr,Key_Type E_Num)
{
    int pos;
    Key_Node *k_ptr;
    Data_Node *d_ptr;
    
    if(Tree_ptr -> root == NULL)
    {
        pos = -1;
        d_ptr = NULL;            
    }
    else if(Tree_ptr -> root_type == 0)
    {
        d_ptr = (Data_Node*)(Tree_ptr -> root);
    }
    else
    {
        k_ptr = (Key_Node*)(Tree_ptr -> root);
        while(k_ptr -> Child_Type == 1)
        {
            pos = Find_Branch(k_ptr,E_Num);
            k_ptr = k_ptr -> Children[pos];            
        }
        pos = Find_Branch(k_ptr,E_Num);
        d_ptr = k_ptr -> Children[pos];
    }
    return d_ptr;    
}

int Height(BPlusTree *Tree_ptr)
{
    int height;
    Key_Node *k_ptr;
    
    if(Tree_ptr -> root == NULL)
    {
        height = -1;            
    }
    else if(Tree_ptr -> root_type == 0)
    {
        height = 0;     
    }
    else
    {
        k_ptr = (Key_Node*)(Tree_ptr -> root);
        height = 1;
        while(k_ptr -> Child_Type == 1)
        {
            k_ptr = k_ptr -> Children[0];
            height++;            
        }    
    }
    return height;    
}

int getNumRecords(BPlusTree *Tree_ptr)
{
    int NumRecords;
    Data_Node *d_ptr;
    
    if(Tree_ptr -> root == NULL)
    {
        NumRecords = 0;            
    }
    else if(Tree_ptr -> root_type == 0)
    {
        d_ptr = (Data_Node*)(Tree_ptr -> root);
        NumRecords = d_ptr -> Active_Data;         
    }
    else
    {
        d_ptr = Tree_ptr -> data_lptr;
        NumRecords = 0;
        while(d_ptr != NULL)
        {
            NumRecords = NumRecords + d_ptr -> Active_Data;
            d_ptr = d_ptr -> next;            
        }    
    }
    return NumRecords;    
}

void RangeSearch(BPlusTree *Tree_ptr,Key_Type Emp_Num1,Key_Type Emp_Num2)
{
    Data_Node *d_ptr1,*d_ptr2;
    Key_Type temp;
    int i;
    
    if(Tree_ptr -> root == NULL)
    {
        printf("Your database is empty\n");            
    }
    else if(Emp_Num1 < 0 || Emp_Num2 < 0)
    {
        printf("ERROR!-->Wrong type of input.Employee number must be positive");     
    }
    else
    {
        if(Emp_Num1 == Emp_Num2)
        {
            Search(Tree_ptr,Emp_Num1);                  
        }
        else
        {
            if(Emp_Num2 < Emp_Num1)
            {
                temp = Emp_Num1;
                Emp_Num1 = Emp_Num2;
                Emp_Num2 = temp;              
            }
    
            d_ptr1 = Search_Data_Node(Tree_ptr,Emp_Num1);
            d_ptr2 = Search_Data_Node(Tree_ptr,Emp_Num2);
            i = 0;
            while(LT((d_ptr1 -> Data_Arr[i]).Emp_Num,Emp_Num1) && i < d_ptr1 -> Active_Data)
            {
                i++;                 
            }
            if(i == d_ptr1 -> Active_Data)
            {
                d_ptr1 = d_ptr1 -> next;
                i = 0;     
            }
            
            if(d_ptr1 != NULL)
            {
                if(d_ptr1 == d_ptr2)
                {
                    while(i < d_ptr1 -> Active_Data)
                    {
                        printf("%d %s %s %s %s\n",(d_ptr1 -> Data_Arr[i]).Emp_Num,(d_ptr1 -> Data_Arr[i]).Emp_Name,(d_ptr1 -> Data_Arr[i]).Designation,(d_ptr1 -> Data_Arr[i]).Emp_Addr,(d_ptr1 -> Data_Arr[i]).Phone_Num);
                        i++;    
                    }          
                }
                else
                {
                    while(d_ptr1 != d_ptr2)
                    {
                        while(i < d_ptr1 -> Active_Data)
                        {
                            printf("%d %s %s %s %s\n",(d_ptr1 -> Data_Arr[i]).Emp_Num,(d_ptr1 -> Data_Arr[i]).Emp_Name,(d_ptr1 -> Data_Arr[i]).Designation,(d_ptr1 -> Data_Arr[i]).Emp_Addr,(d_ptr1 -> Data_Arr[i]).Phone_Num);
                            i++;        
                        }
                        d_ptr1 = d_ptr1 -> next;
                        i = 0;                 
                    }
                    i = 0;
                    while((LT((d_ptr1 -> Data_Arr[i]).Emp_Num,Emp_Num2) || !NEQ((d_ptr1 -> Data_Arr[i]).Emp_Num,Emp_Num2)) && i < d_ptr1 -> Active_Data)
                    {
                        printf("%d %s %s %s %s\n",(d_ptr1 -> Data_Arr[i]).Emp_Num,(d_ptr1 -> Data_Arr[i]).Emp_Name,(d_ptr1 -> Data_Arr[i]).Designation,(d_ptr1 -> Data_Arr[i]).Emp_Addr,(d_ptr1 -> Data_Arr[i]).Phone_Num);
                        i++;                 
                    }          
                }
            }
            else
            {
                printf("Your database does not contain any record in the range you have specified\n");    
            }
        }
    }
}

void PrintDatabase(BPlusTree *Tree_ptr)
{
    Data_Node *d_ptr;
    int i;
    
    if(Tree_ptr -> root == NULL)
    {
        printf("Your database is empty");            
    }
    else
    {
        d_ptr = Tree_ptr -> data_lptr;
        
        while(d_ptr != NULL)
        {
            for(i = 0;i < d_ptr -> Active_Data;i++)
            {  
                printf("%d %s %s %s %s\n",(d_ptr -> Data_Arr[i]).Emp_Num,(d_ptr -> Data_Arr[i]).Emp_Name,(d_ptr -> Data_Arr[i]).Designation,(d_ptr -> Data_Arr[i]).Emp_Addr,(d_ptr -> Data_Arr[i]).Phone_Num);      
            }
            d_ptr = d_ptr -> next;            
        }    
    }     
}


void Print_Tree(BPlusTree *Tree_ptr)
{
    Key_Node *kptr;
    if(Tree_ptr -> root == NULL)
    {
        printf("Tree is empty\n");            
    }
    else if(Tree_ptr -> root_type == 0)
    {
        PrintDatabase(Tree_ptr);     
    }
    if(Tree_ptr -> root_type == 1)
    {
        kptr = (Key_Node*)(Tree_ptr -> root);
        PrintStructure(kptr);
        PrintDatabase(Tree_ptr);              
    }     
}

void PrintStructure(Key_Node *kptr)
{
    int i;
    if(kptr -> Child_Type == 0)
    {
        for(i = 0;i < kptr -> Active_Keys;i++)
        {
            printf("%d ",kptr -> Key_Arr[i]);      
        }
        printf("\n");        
    }
    else
    {
        for(i = 0;i <= kptr -> Active_Keys;i++)
        {
            PrintStructure(kptr -> Children[i]);      
        }
        for(i = 0;i < kptr -> Active_Keys;i++)
        {
            printf("%d ",kptr -> Key_Arr[i]);      
        }
        printf("\n");    
    }     
}
