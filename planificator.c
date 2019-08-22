#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define BUFFMAX 100

typedef struct proces{
	char nume[20];
	int timp;
	int power;
	int plus;
	int minus;
}Proces;

typedef struct queue{
	Proces *proces;
	struct queue *next;
}Queue;

typedef struct stack{
	Proces *proces;
	struct stack *next;
}Stack;

int is_empty_stack(Stack *top){
	if (top == NULL) return 1;
	else return 0;
}

int is_empty_queue(Queue *top){
	if (top == NULL) return 1;
	else return 0;
}

Stack *push(Stack *top, Proces *proces){
	if (is_empty_stack(top) == 1){
		top = (Stack*)malloc(sizeof(Stack));
		top->proces = proces;
		top->next = NULL;
		return top;
	}
	Stack *new_top;
	new_top = (Stack*)malloc(sizeof(Stack));
	new_top->proces = proces;
	new_top->next = top;
	return new_top;
}

Stack *pop(Stack *top){
	if (is_empty_stack(top) == 1){
		printf("Stiva e goala, nothing to pop.\n");
		return top;
	}
	Stack *tmp = top;
	top = top->next;
	free(tmp);
	return top;
}

Stack *pop_everything(Stack *top){
	if (is_empty_stack(top) == 1){
		printf("Stiva e goala, nothing to pop.\n");
		return top;
	}
	Stack *tmp = top;
	top = top->next;
	free(tmp->proces);
	free(tmp);
	return top;
}

Proces *top(Stack *top){
	if(is_empty_stack(top) == 1){
		printf("Stiva e goala, nothing to top.\n");
		return NULL;
	}
	return top->proces;
}

Queue *enqueue(Queue *q, Proces *proces){
	if(is_empty_queue(q) == 1){
		q = (Queue*)malloc(sizeof(Queue));
		q->proces = proces;
		q->next = NULL;
		return q;
	}
	Queue *tmp = q;
	while(tmp->next) tmp = tmp->next;
	Queue *new;
	new = (Queue*)malloc(sizeof(Queue));
	new->proces = proces;
	tmp->next = new;
	new->next = NULL;
	return q;
}

Queue *dequeue(Queue *q){
	if (is_empty_queue(q) == 1){
		printf("Coada e goala, nothing to dequeue.\n");
		return NULL;
	}
	Queue *tmp = q;
	q = q->next;
	free(tmp);
	return q;
}

Proces *first(Queue *q){
	if (is_empty_queue(q) == 1){
		printf("Coada e goala, nothing to show.\n");
		return NULL;
	}
	return q->proces;
}

void list_any_queue(Queue *q){
	if (is_empty_queue(q) == 1)
		printf("Coada este goala.\n");
	Queue *tmp = q;
	while(tmp){
		printf("%s ",tmp->proces->nume);
		printf("%d ",tmp->proces->timp);
		printf("%d ",tmp->proces->power);
		printf("\n");
		tmp = tmp->next;
	}
}

void list_the_stack(Stack *top){
	if (is_empty_stack(top) == 1){
		printf("Stiva este goala.\n");
	}
	else{
	printf("%s ", top->proces->nume);
	printf("%d ", top->proces->timp);
	printf("%d\n", top->proces->power);
	}
}

Queue *new_processes(char *command, Proces *new, Queue *ready){
	char *tok;
	char *ptr = command;

	tok = strtok(ptr, " ");
	ptr = NULL;

	while ((tok = strtok(ptr, " ")) != NULL){
		new = (Proces*)malloc(sizeof(Proces));
		strcpy(new->nume,tok);
		ptr = NULL;

		tok = strtok(ptr, " ");
		new->timp = atoi(tok);
		ptr = NULL;

		tok = strtok(ptr, " ");
		new->power = atoi(tok);
		ptr = NULL;

		new->plus = 0;
		new->minus = 0;

		printf("Procesul %s a fost adaugat in Ready\n",new->nume);

		ready = enqueue(ready,new);
	}
	return ready;
}

FILE *show(Stack *top, FILE *output){
	if(is_empty_stack(top) == 1){
		fprintf(output, "\n");
	}
	else{
		fprintf(output, "%s %d\n", top->proces->nume, top->proces->timp);
	}
	return output;
}

Stack* time(Stack *top, int *contor){
	if(is_empty_stack(top) == 1){
		return top;
	}
	top->proces->timp = top->proces->timp - 1;
	*contor = *contor + 1;
	printf("Timpul de la %s a scazut si este %d\n",top->proces->nume, top->proces->timp);
	return top;
}

Stack* fcfs(Queue **ready, Stack **running){
	if(is_empty_stack(*running) == 1 && is_empty_queue(*ready) == 1){
		printf("testif1\n");
		return *running;
	}
	else if(is_empty_stack(*running) == 1 && is_empty_queue(*ready) == 0){
		*running = push(*running,first(*ready));
		*ready = dequeue(*ready);
		printf("testif2\n");
		return *running;
	}
	else if((*running)->proces->timp == 0 && is_empty_queue(*ready) == 1){
		*running = pop_everything(*running);
		*running = NULL;
		printf("testif3\n");
		return *running;
	}
	else if((*running)->proces->timp == 0 && is_empty_queue(*ready) == 0){
		*running = pop_everything(*running);
		*running = push(*running,first(*ready));
		*ready = dequeue(*ready);
		printf("testif4\n");
		return *running;
	}
	return *running;
}

void chopN(char *str, int n)
{
    assert(n != 0 && str != 0);
    size_t len = strlen(str);
    if (n > len)
        return;
    memmove(str, str+n, len - n + 1);
    char *tmp = strdup(str);
    sscanf(tmp,"%s\n",str);
}

Queue* search(char* to_find, Queue* q){
	Queue *tmp = q;
	Queue *gasit = NULL;

	while(tmp != NULL){
		if(strcmp(tmp->proces->nume,to_find) == 0){
			gasit = tmp;
			printf("Found it\n");
		}
		tmp = tmp->next;
	}
	return gasit;
}

Queue* find_process(char* termen, Queue* q){
	Queue *gasit;
	chopN(termen,2);
	gasit = search(termen,q);
	if(gasit == NULL) return NULL;
	else return gasit;
}

Proces* new_single_proces(Proces *input, Proces* output){
	output = (Proces*)malloc(sizeof(Proces));
	strcpy(output->nume,input->nume);
	output->timp = input->timp;
	output->power = input->power;
	output->plus = input->plus;
	output->minus = input->minus;
	return output;
}

Queue* remove_node(Queue *q, Proces *to_remove){
	Queue *tmp = q;	
	if(q->proces == to_remove){
		q = q->next;
		free(tmp->proces);
		free(tmp);
		return q;
	}
	Queue *de_sters;
	while(tmp->next != NULL){
		if(tmp->next->proces == to_remove){
			de_sters = tmp->next;
			tmp->next = tmp->next->next;
			free(de_sters->proces);
			free(de_sters);
			return q;
		}
		tmp = tmp->next;
	}
	return q;
}

Queue* smallest_process(Queue* q){

	Queue *tmp = q;
	Queue *gasit = q;
	while(tmp != NULL){
		if(tmp->proces->timp < gasit->proces->timp){
			gasit = tmp;
		}
		tmp = tmp->next;
	}
	return gasit;
}

Stack* sjf(Queue **ready, Stack **running, Proces **gasit, Proces **new){
	if(is_empty_stack(*running) == 1 && is_empty_queue(*ready) == 1){
		printf("testif1_sjf\n");
		return *running;
	}
	else if(is_empty_stack(*running) == 1 && is_empty_queue(*ready) == 0){
		*gasit = smallest_process(*ready)->proces;
		*new = new_single_proces(*gasit,*new);
		*running = push(*running,*new);
		*ready = remove_node(*ready,*gasit);
		printf("testif2_sjf\n");
		return *running;
	}
	else if((*running)->proces->timp == 0 && is_empty_queue(*ready) == 1){
		*running = pop_everything(*running);
		*running = NULL;
		printf("testif3_sjf\n");
		return *running;
	}
	else if((*running)->proces->timp == 0 && is_empty_queue(*ready) == 0){
		printf("testif4_sjf\n");
		*running = pop_everything(*running);
		*gasit = smallest_process(*ready)->proces;
		*new = new_single_proces(*gasit,*new);
		*running = push(*running,*new);
		*ready = remove_node(*ready,*gasit);
		return *running;
	}
	return *running;
}

void command_add(Stack **running, Queue **ready, char **comanda, Proces **new, int *contor){
	*ready = new_processes(*comanda,*new,*ready);
	*running = time(*running,contor);  // timp implicit
}

void command_wait(Stack **running, Queue **waiting, Queue **ready, int *contor){
	*waiting = enqueue(*waiting,top(*running));
	*running = pop(*running);
	*running = time(*running,contor); // timp implicit
}

Proces* count_event(Proces *proces){
	 proces->plus++;
	 return proces;
}

Proces* check_upgrade(Proces *proces){
		
		if (proces->minus == 2){
			proces->minus = 0;
			proces->power--;
			printf("Putere scazuta\n");
			return proces;
		}
		else if (proces->plus == 2){
			proces->plus = 0;
			proces->power++;
			printf("Putere primita\n");
			return proces;
		}
		else return proces;
}

void command_event(Stack **running,Queue **waiting, Queue **ready, Proces **gasit, char **line, Proces **new, int *contor){
	*gasit = find_process(*line,*waiting)->proces;
		if(*gasit != NULL){
			*new = new_single_proces(*gasit,*new);
			*new = count_event(*new);
			*new = check_upgrade(*new);
			printf("Event_counted\n");
			*ready = enqueue(*ready,*new);
			*waiting = remove_node(*waiting,*gasit);
			*running = time(*running,contor); // timp implicit
		}
}

void record_data(int *planificare, int *cuanta, int* nivele, char *line){
	*planificare = atoi(&line[0]);
	if(&line[2] != NULL)
		*cuanta = atoi(&line[2]);
	if(&line[4] != NULL)
		*nivele = atoi(&line[4]);
}

void core_function_rr(int *contor, Proces **gasit, Proces **new, Queue **ready, Stack **running){
	*gasit = (*running)->proces;
	*new = new_single_proces(*gasit,*new);
	*ready = enqueue(*ready,*new);
	*running = pop_everything(*running);
	*running = push(*running,first(*ready));
	*contor = 0;
	*ready = dequeue(*ready);
}

Stack* rr(int *contor, Stack **running, Queue **ready, int *cuanta, Proces **gasit, Proces **new){
	if(is_empty_stack(*running) == 1 && is_empty_queue(*ready) == 1){
		printf("testif1_rr\n");
		return *running;
	}
	else if(is_empty_stack(*running) == 1 && is_empty_queue(*ready) == 0){
		*running = push(*running,first(*ready));
		*contor = 0;
		*ready = dequeue(*ready);
		printf("testif2_rr\n");
		return *running;
	}
	else if((*running)->proces->timp == 0 && is_empty_queue(*ready) == 1){
		*running = pop_everything(*running);
		*running = NULL;
		printf("testif3_rr\n");
		return *running;
	}
	else if(*contor == *cuanta && is_empty_queue(*ready) == 1){
		core_function_rr(contor,gasit,new,ready,running);
		printf("testif4_rr\n");
		return *running;
	}
	else if((*running)->proces->timp == 0 && is_empty_queue(*ready) == 0){
		*running = pop_everything(*running);
		*running = push(*running,first(*ready));
		*contor = 0;
		*ready = dequeue(*ready);
		printf("testif5_rr\n");
		return *running;
	}
	else if(*contor == *cuanta && is_empty_queue(*ready) == 0){
		core_function_rr(contor,gasit,new,ready,running);
		printf("testif6_rr\n");
		return *running;
	}
	return *running;
}

Queue* find_maximum_power(Queue *q, int *nivele){
	Queue *tmp = q;
	Queue *gasit = q;
	int i = *nivele;
	
	while(i > 0){
		tmp = q;
		while(tmp != NULL){
			if(tmp->proces->power == i){
				gasit = tmp;
				return gasit;
			}
			tmp = tmp->next;
		}
		i = i-1;
	}
	return gasit;
}

void core_pp(Proces **new, Proces **gasit, Stack **running, int *contor){
	*new = new_single_proces(*gasit,*new);
	*running = push(*running,*new);
	*contor = 0;
}

Stack* count_exit(Stack *running){
		running->proces->minus++;
		return running;
}


Stack* bonus_function(Stack* running, int bonus){
	if(bonus == 1){
		running = count_exit(running);
		running->proces = check_upgrade(running->proces);
		return running;
	}
	else
		return running;
}

Stack* pp(Queue **ready, Stack **running, Proces **gasit, Proces **new, int *nivele, int *contor, int *cuanta, int bonus){
	
	if (is_empty_stack(*running) == 1){
		if(is_empty_queue(*ready) == 1){
			printf("testif1_pp\n");
			return *running;
		}
		else if(is_empty_queue(*ready) == 0){
			*gasit = find_maximum_power(*ready,nivele)->proces;
			core_pp(new,gasit,running,contor);
			*ready = remove_node(*ready,*gasit);
			printf("testif2_pp\n");
			return *running;
		}
	}
	else if(is_empty_stack(*running) == 0){
		if(is_empty_queue(*ready) == 0){
			*gasit = find_maximum_power(*ready,nivele)->proces;
			if((*gasit)->power > (*running)->proces->power){
				*running = bonus_function(*running,bonus);
				*new = new_single_proces((*running)->proces,*new);
				*ready = enqueue(*ready,*new);
				*running = pop_everything(*running);
				core_pp(new,gasit,running,contor);
				*ready = remove_node(*ready,*gasit);
				printf("testif3_pp\n");
				return *running;
			}
			else if((*running)->proces->timp == 0){
				*running = pop_everything(*running);
				*gasit = find_maximum_power(*ready,nivele)->proces;
				core_pp(new,gasit,running,contor);
				*ready = remove_node(*ready,*gasit);
				printf("testif4_pp\n");
				return *running;
			}
			else if(*contor == *cuanta){
				*running = bonus_function(*running,bonus);
				*new = new_single_proces((*running)->proces,*new);
				*ready = enqueue(*ready,*new);
				*running = pop_everything(*running);
				*gasit = find_maximum_power(*ready,nivele)->proces;
				core_pp(new,gasit,running,contor);
				*ready = remove_node(*ready,*gasit);
				printf("testif_5pp\n");
				return *running;
			}
			else if((*running)->proces->timp == 0){
				*running = pop_everything(*running);
				core_pp(new,gasit,running,contor);
				*ready = remove_node(*ready,*gasit);
				printf("testif_6pp\n");
				return *running;
			}
		}
		else if(is_empty_queue(*ready) == 1){
			if(*contor == *cuanta){
				*new = new_single_proces((*running)->proces,*new);
				*ready = enqueue(*ready,*new);
				*running = pop_everything(*running);
				*new = new_single_proces(first(*ready),*new);
				*running = push(*running,*new);
				*contor = 0;
				*ready = dequeue(*ready);
				printf("testif7_pp\n");
				return *running;
			}
			if((*running)->proces->timp == 0){
				*running = pop_everything(*running);
				*running = NULL;
				printf("testif_8pp\n");
				return *running;
			}
		}
	}
	return *running;
}

int main (int argc, char **argv){

	Proces *new = NULL;
	Proces *gasit = NULL;
	Queue *ready = NULL;
	Stack *running = NULL;
	Queue *waiting = NULL;
	int planificare = 0;
	int cuanta = 0;
	int nivele = 0;
	int contor = 0;
	char *line;
	FILE *f;
	FILE *p;
	char comanda[BUFFMAX];

	f = fopen(argv[1],"r");
	p = fopen(argv[2],"w");

	if (f == NULL || p == NULL)
		printf("Eroare la deschiderea fisierului.\n");
	else{
		fgets(comanda, BUFFMAX, f);
		line = strdup(comanda);
		record_data(&planificare,&cuanta,&nivele,line); // inca nu merge

		while(fgets(comanda, BUFFMAX, f) != NULL){
			switch(comanda[0]){
				case 'a':
					line = strdup(comanda);
					command_add(&running,&ready,&line,&new,&contor);
					break;
				case 'm':
					line = strdup(comanda);
					command_add(&running,&ready,&line,&new,&contor);
					break;
				case 's':
					p = show(running,p);
					break;
				case 'w':
					command_wait(&running,&waiting,&ready,&contor);
					break;
				case 't':
					running = time(running,&contor);
					break;
				case 'e':
					line = strdup(comanda);
					command_event(&running,&waiting,&ready,&gasit,&line,&new,&contor);
					break;
			}
			switch(planificare){
				case 1:
					running = fcfs(&ready,&running);
					break;
				case 2:
					running = sjf(&ready,&running,&gasit,&new);
					break;
				case 3:
					running = rr(&contor,&running,&ready,&cuanta,&gasit,&new);
					break;
				case 4:
					running = pp(&ready,&running,&gasit,&new,&nivele,&contor,&cuanta,0);
					break;
				case 5:
					running = pp(&ready,&running,&gasit,&new,&nivele,&contor,&cuanta,1);
			}
		}
		fclose(p);
		fclose(f);
	}
	
	printf("\nStats about processes:\n");
	printf("Lista de waiting:\n");
	list_any_queue(waiting);

	printf("Lista de running:\n");
	list_the_stack(running);

	printf("Lista de ready:\n");
	list_any_queue(ready);

	printf("Contorul este: %d\n",contor);

	return 0;
}