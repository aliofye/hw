#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    char* data;
    struct node* next;
    struct node* prev;

} node_t;

void generate_linked_list(node_t **head, char* str);
void calculate(node_t **head, char op);
void delete_node(node_t **head);
int get_length(char* str);
void test_print(node_t *list);


int main(int argc, char const *argv[])
{
	
	char str[100];

	scanf ("%s",str);

	
	node_t* list = NULL;
	
	generate_linked_list(&list, str);

	calculate(&list, '-');
	calculate(&list, '/');
	calculate(&list, '+');
	calculate(&list, '*');
	
	//solution
	printf("%s\n", list->next->data);
	return 0;
}

void test_print(node_t *list){
	while(list != NULL){
		printf("(%s)->", list->data);
		list = list->next;
	}
	printf("\n");
}

void calculate(node_t **head, char op){
	
	//iterate through list until the end because the expression was parsed backwards (probably should change this)
	while((*head)->next != NULL){
		(*head) = (*head)->next;
	}

	//iterate through list until you find operator
	while((*head)->prev != NULL){
		//if operator found, calculate
		if((*head)->data[0] == op){
			int lhs = atoi((*head)->next->data);
			int rhs = atoi((*head)->prev->data);

			
			

			switch(op){
				
				case '-':{
					int total = lhs-rhs;
					//convert total into a string
					char total_str[12];
					sprintf(total_str, "%i", total);
					//assign total
					(*head)->data = NULL;
					(*head)->data = malloc(strlen(total_str) + 1);
					strcpy((*head)->data, total_str);
					//delete operands from list
					delete_node(&((*head)));
					//print operation
					//printf("%i - %i = %i \n",lhs,rhs,total);

					break;
				}
				case '/':{
					int total = lhs/rhs;
					//convert total into a string
					char total_str[12];
					sprintf(total_str, "%i", total);
					//assign total
					(*head)->data = NULL;
					(*head)->data = malloc(strlen(total_str) + 1);
					strcpy((*head)->data, total_str);
					//delete operands from list
					delete_node(&((*head)));
					//print operation
					//printf("%i / %i = %i \n",lhs,rhs,total);
					
					break;
				}
				case '+':{
					int total = lhs+rhs;
					//convert total into a string
					char total_str[12];
					sprintf(total_str, "%i", total);
					//assign total
					(*head)->data = NULL;
					(*head)->data = malloc(strlen(total_str) + 1);
					strcpy((*head)->data, total_str);
					//delete operands from list
					delete_node(&((*head)));
					//print operation
					//printf("%i + %i = %i \n",lhs,rhs,total);

					break;
				}
				case '*':{
					int total = lhs*rhs;
					//convert total into a string
					char total_str[12];
					sprintf(total_str, "%i", total);
					//assign total
					(*head)->data = NULL;
					(*head)->data = malloc(strlen(total_str) + 1);
					strcpy((*head)->data, total_str);
					//delete operands from list
					delete_node(&((*head)));
					//print operation
					//printf("%i * %i = %i \n",lhs,rhs,total);

					break;
				}
			}

		}

		//iterate
		(*head) = (*head)->prev;
	}

	//test_print(*head);
}

void delete_node(node_t **node){
	//restablish links
	if((*node)->prev->prev != NULL){
		(*node)->prev = (*node)->prev->prev;

		//free memory allocated to string
		free((*node)->prev->next->data);
		//free memory allocated to node
		free((*node)->prev->next);
		//restablish links
		(*node)->prev->next = (*node);
	} else {
		// //free((*node)->prev->data);
		// free((*node)->prev);
	}
	
	//restablish links
	if((*node)->next->next != NULL){
		(*node)->next = (*node)->next->next;

		//free memory allocated to string
		free((*node)->next->prev->data);
		//free memory allocated to node
		free((*node)->next->prev);
		//restablish links
		(*node)->next->prev = (*node);
	} else {
		// //free((*node)->next->data);
		// free((*node)->next);
	}
	
}

int get_length(char* input_str){
    int count = 0;
    while(input_str[count] != '\0'){
        count++;
    }

    return count;
}

void generate_linked_list(node_t **head, char* str){
	
	int length = get_length(str);
	

	int i;
	for (i = 0; i<length; ++i){	
		char num[12] = {0};
		node_t* temp = NULL;
		temp = malloc(sizeof(node_t));
		//if char is a number
		if(str[i] >= '0' && str[i] <= '9'){
			
			int k=0;
			
			while(str[i] >= '0' && str[i] <= '9'){	
				num[k] = str[i];
				i++;
				k++;
			}

			i--;
			
			temp->data = malloc(strlen(num) + 1);
			strcpy(temp->data, num);
			temp->next = *head;
			temp->prev = NULL;
			//maintain double link
			if(*head != NULL){
				(*head)->prev = temp;
			}
			*head = temp;

		} else {//char is an operator
			num[0] = str[i];
			temp->data = malloc(strlen(num) + 1);
			strcpy(temp->data, num);
			temp->next = *head;
			temp->prev = NULL;
			//maintain double link
			if(*head != NULL){
				(*head)->prev = temp;
			}
			*head = temp;
		}
	}
}
