#include<stdio.h>
#include<conio.h>
#define MAXKEYS 4
#define MINKEYS 2
#define ARY 5
typedef int Key_Type;
typedef struct Item_Tag
        {
            Key_Type Key;       
        } Item_Type;
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
            Item_Type Data_Arr[ARY + 1];
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
status_code Insert(BPlusTree *Tree_ptr,Item_Type item);
int Find_Data_Pos(Data_Node *dptr,Item_Type item);
status_code Delete(BPlusTree *Tree_ptr,Item_Type item);

main()
{
    BPlusTree Tree;
    int i,h;
    Item_Type d;
    Data_Node *ptr;
    Key_Node *k,*j;
    status_code SC = SUCCESS;
    InitializeTree(&Tree);
    /*for(i = 0;i < 21;i++)
    {
        printf("Enter the key to insert\n");
        scanf("%d",&d.Key);
        //d.Key = i;
        SC = Insert(&Tree,d);
        printf("SC = %d\n",SC);      
    }*/
    d.Key = 2;
    SC = Insert(&Tree,d);
    d.Key = 5;
    SC = Insert(&Tree,d);
    d.Key = 7;
    SC = Insert(&Tree,d);
    d.Key = 50;
    SC = Insert(&Tree,d);
    d.Key = 39;
    SC = Insert(&Tree,d);
    d.Key = 22;
    SC = Insert(&Tree,d);
    d.Key = 1;
    SC = Insert(&Tree,d);
    d.Key = 9;
    SC = Insert(&Tree,d);
    d.Key = 8;
    SC = Insert(&Tree,d);
    d.Key = 18;
    SC = Insert(&Tree,d);
    d.Key = 99;
    SC = Insert(&Tree,d);
    d.Key = 11;
    SC = Insert(&Tree,d);
    d.Key = 32;
    SC = Insert(&Tree,d);
    d.Key = 15;
    SC = Insert(&Tree,d);
    d.Key = 45;
    SC = Insert(&Tree,d);
    d.Key = 23;
    SC = Insert(&Tree,d);
    d.Key = 30;
    SC = Insert(&Tree,d);
    d.Key = 44;
    SC = Insert(&Tree,d);
    d.Key = 52;
    SC = Insert(&Tree,d);
    d.Key = 56;
    SC = Insert(&Tree,d);
    d.Key = 51;
    SC = Insert(&Tree,d);
     ptr = Tree.data_lptr;
    while(ptr != NULL)
    {
        for(i = 0;i < ptr -> Active_Data;i++)
        {
            printf("%d ",(ptr -> Data_Arr[i]).Key);      
        }
        printf("\n");
        ptr = ptr -> next;          
    }
    d.Key = 9;
    SC = Delete(&Tree,d);
    ptr = Tree.data_lptr;
    while(ptr != NULL)
    {
        for(i = 0;i < ptr -> Active_Data;i++)
        {
            printf("%d ",(ptr -> Data_Arr[i]).Key);      
        }
        printf("\n");
        ptr = ptr -> next;          
    }
    d.Key = 39;
    SC = Delete(&Tree,d);
    ptr = Tree.data_lptr;
    while(ptr != NULL)
    {
        for(i = 0;i < ptr -> Active_Data;i++)
        {
            printf("%d ",(ptr -> Data_Arr[i]).Key);      
        }
        printf("\n");
        ptr = ptr -> next;          
    }
    /*d.Key = 2;
    SC = Delete(&Tree,d);
    ptr = Tree.data_lptr;
    while(ptr != NULL)
    {
        for(i = 0;i < ptr -> Active_Data;i++)
        {
            printf("%d ",(ptr -> Data_Arr[i]).Key);      
        }
        printf("\n");
        ptr = ptr -> next;          
    }
    d.Key = 7;
    SC = Delete(&Tree,d);
    ptr = Tree.data_lptr;
    while(ptr != NULL)
    {
        for(i = 0;i < ptr -> Active_Data;i++)
        {
            printf("%d ",(ptr -> Data_Arr[i]).Key);      
        }
        printf("\n");
        ptr = ptr -> next;          
    }
    d.Key = 5;
    SC = Delete(&Tree,d);
    ptr = Tree.data_lptr;
    while(ptr != NULL)
    {
        for(i = 0;i < ptr -> Active_Data;i++)
        {
            printf("%d ",(ptr -> Data_Arr[i]).Key);      
        }
        printf("\n");
        ptr = ptr -> next;          
    }*/
    ptr = Tree.data_lptr;
    getch();
    if(ptr != NULL && ptr -> parent != NULL)
    {
    while(ptr != NULL)
    {
        k = ptr -> parent;
        for(h = 0;h < k -> Active_Keys;h++)
        {
            printf("p = %d\n",k -> Key_Arr[h]);      
        }
        for(i = 0;i < ptr -> Active_Data;i++)
        {
            printf("%d ",(ptr -> Data_Arr[i]).Key);      
        }
        printf("\n");
        ptr = ptr -> next;          
    }
    k = (Key_Node*)Tree.root;
    printf("\n%d",k -> Active_Keys);
    
    for(i = 0;i < k -> Active_Keys;i++)
    {
        if(i==0)
        {
            printf("root = %d\n",k -> Key_Arr[i]);
            if(k -> Child_Type == 1)
            {
           j = (Key_Node*)(k -> Children[0]);
            printf("%d %d\n",j -> Key_Arr[0],j -> Key_Arr[1]);
            j = (Key_Node*)(k -> Children[1]);
            printf("%d %d %d\n",j -> Key_Arr[0],j -> Key_Arr[1],j -> Active_Keys);
            //j = (Key_Node*)(k -> Children[2]);
            //printf("keys = %d %d active %d\n",j -> Key_Arr[0],j -> Key_Arr[1],j -> Active_Keys);
            }        
        }
    }
    printf("reaching here?\n\n");
    printf("\n\n\n");
    ptr = Tree.data_lptr;
    k = ptr -> parent;
    while(k != NULL)
    {
        i = k -> Active_Keys;
        for(h = 0;h < i;h++)
        {
            printf("%d ",k -> Key_Arr[h]);      
        }
        k = k -> parent;          
    }
    }
    getch();      
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

status_code Insert(BPlusTree *Tree_ptr,Item_Type item)
{
    status_code SC = SUCCESS;
    Data_Node *data_ptr,*d,*new_data,*current_data;
    Key_Node *key_ptr,*parent_ptr,*current_ptr,*new_ptr;
    Key_Type new_Key;
    int i,pos,done;
    if(Tree_ptr -> root == NULL)/*Root is NULL*/
    {
        data_ptr = (Data_Node*)malloc(sizeof(Data_Node));
        if(data_ptr == NULL)
        {
            SC = FAILURE;            
        }
        else
        {
            data_ptr -> Data_Arr[0] = item;
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
        data_ptr -> Data_Arr[data_ptr -> Active_Data] = item;
        i = data_ptr -> Active_Data - 1;
        //Sort the data node-Insertion sort
        while((i >= 0) && (LT(item.Key,(data_ptr -> Data_Arr[i]).Key)))
        {
            data_ptr -> Data_Arr[i + 1] = data_ptr -> Data_Arr[i];
            data_ptr -> Data_Arr[i] = item;
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
                
                //Insert data into the new data node from the one which has become full
                for(i = 0;i < MINKEYS + 1;i++)
                {
                    new_data -> Data_Arr[i] = current_data -> Data_Arr[MINKEYS + 1 + i];      
                }
                
                current_data -> Active_Data = MINKEYS + 1;
                new_data -> Active_Data = MINKEYS + 1;
                
                //Insert the key in the key node
                key_ptr -> Key_Arr[0] = (new_data -> Data_Arr[0]).Key;
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
            pos = Find_Branch(key_ptr,item.Key);
            key_ptr = key_ptr -> Children[pos];              
        }
        //Find the branch of the data node corresponding to the new Key of the data to be inserted
        pos = Find_Branch(key_ptr,item.Key);
        data_ptr = key_ptr -> Children[pos];
        
        //Insert the data and sort it on key-Insertion sort
        data_ptr -> Data_Arr[data_ptr -> Active_Data] = item;
        i = data_ptr -> Active_Data - 1;
        while((i >= 0) && (LT(item.Key,(data_ptr -> Data_Arr[i]).Key)))
        {
            data_ptr -> Data_Arr[i + 1] = data_ptr -> Data_Arr[i];
            data_ptr -> Data_Arr[i] = item;
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
            printf("heya");
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
                printf("hmm");
                if(new_data -> next != NULL)
                {
                    (new_data -> next) -> prev = new_data;
                }
                
                //Insert data into the new data node from the one which is full
                for(i = 0;i < MINKEYS + 1;i++)
                {
                    new_data -> Data_Arr[i] = current_data -> Data_Arr[MINKEYS + 1 + i];      
                }
                
                current_data -> Active_Data = MINKEYS + 1;
                new_data -> Active_Data = MINKEYS + 1;
                
                //The key to be inserted into the key node
                new_Key = (new_data -> Data_Arr[0]).Key;
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
                if(item.Key==70)
                {
                printf("%d %d %d\n\n",key_ptr -> Key_Arr[0],key_ptr -> Key_Arr[1],key_ptr -> Key_Arr[2]);
                for(i = 0;i < 4;i++)
                {
                    d = (Data_Node*)(key_ptr -> Children[i]);
                    printf("%d\n",(d -> Data_Arr[0]).Key);          
                }
                }
                printf("idiot");
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
                        done = 0;
                        printf("here");
                        while(!done)
                        {
                            printf("hi");
                            //If the key node which has split was the root
                            if(current_ptr -> parent == NULL)
                            {
                                printf("block1");
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
                                printf("\n%d\n",parent_ptr -> Key_Arr[0]);
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
                                    printf("enuf");
                                    //The key node has to be split
                                    new_ptr = (Key_Node*)malloc(sizeof(Key_Node));
                                    if(new_ptr == NULL)
                                    {
                                        SC = FAILURE;           
                                    }
                                    else
                                    {
                                        current_ptr = parent_ptr;
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
                                }
                            }            
                        }
                        printf("end");          
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

status_code Delete(BPlusTree *Tree_ptr,Item_Type item)
{
    status_code SC = SUCCESS;
    Key_Node *key_ptr,*parent_kptr,*left_kptr,*right_kptr;
    Data_Node *data_ptr,*left_dptr,*right_dptr;
    int i,done,pos;
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
        pos = Find_Data_Pos(data_ptr,item);
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
            pos = Find_Branch(key_ptr,item.Key);
            printf("pos = %d\n\n",pos);
            key_ptr = key_ptr -> Children[pos];              
        }
        //Traverse to the data node which contains the element to be deleted
        pos = Find_Branch(key_ptr,item.Key);
        printf("pos = %d\n\n",pos);
        data_ptr = key_ptr -> Children[pos];
        
        //Find the posision of the element to be deleted in the data node
        pos = Find_Data_Pos(data_ptr,item);
        ("pos = %d\n",pos);
        if(pos == -1)
        {
            //If element is not found then it is a failure condition
            SC = FAILURE;       
        }
        else
        {
            //Element is found
            printf("hi\n");
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
                printf("at least\n\n");
                //Find the parent of the data node
                key_ptr = data_ptr -> parent;
                
                //Immediate right and left data nodes --> To check is they are siblings of the data node
                right_dptr = data_ptr -> next;
                left_dptr = data_ptr -> prev;
                printf("thisthis\n\n");
                if(right_dptr != NULL)
                {
                    //If the immediate right node is not a sibling,then make it NULL
                    if(right_dptr -> parent != key_ptr)
                    {
                        printf("are you");
                        right_dptr = NULL;
                    }              
                }

                if(left_dptr != NULL)
                {
                    //If the immediate left node is not a sibling,then make it NULL
                    printf("trio\n\n");
                    if(left_dptr -> parent != key_ptr)
                    {
                        left_dptr = NULL;             
                    }             
                }
                //If right sibling exists and it can give an element to the deficient node
                if(right_dptr != NULL && right_dptr -> Active_Data > MINKEYS + 1)
                {
                    printf("i am here");
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
                    pos = Find_Branch(key_ptr,(right_dptr -> Data_Arr[0]).Key);
                    //Change the corresponding key in the Key node
                    key_ptr -> Key_Arr[pos - 1] = (right_dptr -> Data_Arr[0]).Key;
                        
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
                    pos = Find_Branch(key_ptr,(data_ptr -> Data_Arr[1]).Key);
                    printf("i am %d\n\n\n\n",pos);
                    //Set the new key
                    key_ptr -> Key_Arr[pos - 1] = (data_ptr -> Data_Arr[0]).Key;
                        
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
                        pos = Find_Branch(key_ptr,(data_ptr -> Data_Arr[0]).Key);
                        //Delete the key
                        for(i = pos;i < key_ptr -> Active_Keys - 1;i++)
                        {
                            key_ptr -> Key_Arr[i] = key_ptr -> Key_Arr[i + 1];
                            key_ptr -> Children[i + 1] = key_ptr -> Children[i + 2];      
                        }
                        
                        if(key_ptr -> Active_Keys > MINKEYS)//If the key node does not become deficient after deletion
                        {
                            key_ptr -> Active_Keys = key_ptr -> Active_Keys - 1;           
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
                        }
                        else
                        {
                            //Key node has to be handled separately now
                            done = 0;
                            while(!done)
                            {
                                printf("again?\n\n");
                                //Decrement the number of active keys and find the parent
                                key_ptr -> Active_Keys = key_ptr -> Active_Keys - 1;
                                parent_kptr = key_ptr -> parent;
                                //Find the branch of the parent we are in
                                pos = Find_Branch(parent_kptr,key_ptr -> Key_Arr[0]);
                                printf("pos = %d idiot\n\n",pos);
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
                                printf("stupid\n\n");
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
                                    printf("enter??\n\n");
                                    if(left_kptr != NULL)
                                    {
                                        printf("hereno?\n\n");
                                        //Find the position of the in-between key in the parent node
                                        pos = Find_Branch(parent_kptr,left_kptr -> Key_Arr[0]);
                                        printf("%d pos = %d %d\n\n",parent_kptr -> Key_Arr[0],pos,(left_kptr -> Key_Arr[0]));
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
                                        printf("play?\n\n");
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
                                                printf("are you?\n\n");
                                                //No restriction on root so decrement the number of active keys
                                                parent_kptr -> Active_Keys = parent_kptr -> Active_Keys - 1;
                                                if(parent_kptr -> Active_Keys != 0)
                                                {
                                                    done = 1;               
                                                }
                                                else
                                                {
                                                    //If the number of keys in the root becomes zero change the root
                                                    printf("this\n\n");
                                                    free(parent_kptr);
                                                    parent_kptr = NULL;
                                                    
                                                    left_kptr -> parent = NULL;
                                                    printf("humy\n\n");
                                                    
                                                    Tree_ptr -> root = left_kptr;
                                                    Tree_ptr -> root_type = 1;
                                                    done = 1;
                                                    printf("haha\n\n");    
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
                                        printf("am i here??");
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
                                            key_ptr -> Active_Keys = key_ptr -> Active_Keys + 1;      
                                        }
                                        printf("hex keys\n");
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
                                        printf("humpty\n\n");
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
                                        printf("dumpty\n\n");
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
                                                printf("and here??\n\n");
                                                //No restriction on root hence decrement the number of active keys
                                                parent_kptr -> Active_Keys = parent_kptr -> Active_Keys - 1;
                                                if(parent_kptr -> Active_Keys != 0)
                                                {
                                                    done = 1;               
                                                }
                                                else
                                                {
                                                    //If number of active keys becomes zero,change the root
                                                    printf("finally done\n\n");
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
                                                printf("huhyht\n\n");
                                                key_ptr = parent_kptr;     
                                            }
                                        }       
                                    }    
                                }
                            }
                        }              
                    }
                    else if(left_dptr != NULL)
                    {
                        printf("I am the stud\n\n");
                        data_ptr -> Active_Data = data_ptr -> Active_Data - 1;
                        
                        for(i = 0;i < data_ptr -> Active_Data;i++)
                        {
                            printf("one\n\n");
                            left_dptr -> Data_Arr[left_dptr -> Active_Data + i] = data_ptr -> Data_Arr[i];
                            left_dptr -> Active_Data = left_dptr -> Active_Data + 1;      
                        }
                        left_dptr -> next = data_ptr -> next;
                        if(data_ptr -> next != NULL)
                        {
                            (data_ptr -> next) -> prev = left_dptr;            
                        }
                        
                        free(data_ptr);
                        data_ptr = NULL;
                        
                        pos = Find_Branch(key_ptr,(left_dptr -> Data_Arr[0]).Key);
                        
                        
                             
                    }    
                }                
            }    
        }        
    }
    return SC;            
}

int Find_Data_Pos(Data_Node *dptr,Item_Type item)
{
    Key_Type k;
    int i;
    k = item.Key;
    i = 0;
    while((i < dptr -> Active_Data) && NEQ(k,(dptr -> Data_Arr[i]).Key))
    {
        i++;         
    }
    if(i == dptr -> Active_Data)
    {
        i = -1;     
    }
    return i;    
}
