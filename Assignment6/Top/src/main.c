#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

struct node
{
	/* data */

	/*Identification of teller*/
	int id;

	/*Number of customers served by the teller*/
	int numCustomers;

	/* Total idle time for a teller*/
	float idleTime;

	/*Total service time for the teller*/
	float serviceTime;

	/*Time refers to the time of the event in case the node is part of an event queue.*/
	float time;

	/**Type refers to the type of event i.e it can be 
	 * CA- Customer Arrival
	 * CS- Customer Serviced
	 * TS- Teller Statistics**/
	char *type;

	/* status used specicfically for tellers where a status of
		0- indicates teller is looking for a person (default initialization)
		1- indicates teller is idle.*/	
	int status;

	/**Pointer to the reference node to which this event refers to
	 * For CA- It would be a customer node
	 * For CS- Again a customer node and,
	 * For TI- Teller Idle.
	 **/
	struct node *ref;

	/*Pointer to the last node of the linked list. Assigned only for the start node.*/
	struct node *end;

	/*Pointer to the next node*/
	struct node *next;

	/* represents the current size of the list */
	int size;
};

/*Global Variable for Time*/
float GlobalTime = 0.0;

/*Stores the number of customers served at any given time*/
int consumers = 0;

struct pair
{
	struct node *n;
	int size;
};

/*Inserts the node corresponding to the event e in the linked list whose starting node is start. */ 
int insertEvent(struct node *e, struct node *start){
	if (start->size == 0){
		start->size = 1;
		start->next = e;
		start->end = e;
		return start->size;
	}
	else{
		struct node *curr = start;
		while(curr->next != NULL){
			if(curr->next->time <= e->time)
				curr = curr->next;
			else{
				e->next = curr->next;
				curr->next = e;
				start->size++;
					return start->size;
				}
			}
			curr->next = e;
			start->size++;
			return start->size;
	}
}

/*Inserts the customer at the end of the TellerQueue.*/
int insertCustomer(struct node *e, struct node *start){
	if (start->size == 0){
		start->next = e;
		start->end = e;
		start->size = 1;		
		return start->size;
	}
	else{
		start->end->next = e;
		start->end = e;
		start->size = start->size + 1;
		return start->size;
	}
}

/* Function to find the shortest queue out of all the teller queues. Random selection in case of equal sizes.*/
int findShortestQ (struct pair *array [], int length){	
	int minIndex = 0;
	int minValue = array[0]->size;
	int minCount = 1;
	for(int i = 1;i<length;i++){
		if(array[i]->size < minValue){
			minValue = array[i]->size;
			minIndex = i;
			minCount = 1;
		}
		else if (array[i]->size == minValue){
			minCount++;
		}
	}
	int j = 0;
	int indexes [minCount];
	for(int i = 0;i<length;i++){
		if(array[i]->size == minValue){
			indexes[j] = i;
			j++;
		}
	}
	int res = rand()%minCount;
	return indexes[res];
}

/* Pops the first element of the queue. Returns the new size of the queue. */
int delete(struct node *start){
	if(start->next != NULL){
		start->size = start->size - 1;
		start->next = start->next->next;
		return start->size;
	}
	else{
		//printf("Start->size: %d\n",start->size);
		printf("Can't delete from an empty list.\n");
		return -1;
	}
}

/*Function for the calculation of mean of the data []*/
float calculateMean(float data[]) {
    float sum = 0.0, mean, SD = 0.0;
    int i;
    for (i = 0; i < 10; ++i) {
        sum += data[i];
    }
    mean = sum / 10;
	return mean;
}

/*Function for the calculation of Standard Deviation of data []*/
float calculateSD(float data[]) {
    float sum = 0.0, mean, SD = 0.0;
    int i;
    for (i = 0; i < 10; ++i) {
        sum += data[i];
    }
    mean = sum / 10;
    for (i = 0; i < 10; ++i)
        SD += pow(data[i] - mean, 2);
    return sqrt(SD / 10);
}

int strtoint (char digits []){
	int device_num = 0;
	if(sscanf(digits, "%d", &device_num) == EOF) {
    	fprintf(stderr, "WARNING: Incorrect value for device\n");
    return 0;
	}
	return device_num;
}

int main(int argc, char *argv []){
	int i = 0;
	FILE* f1 = fopen("data.dat","a");	
	FILE* f = fopen("data.dat","a");
	while(i<2){
		i++;

		/* insertE_ptr is a pointer to function int insertEvent(struct node *e, struct node *start) */
    	int (*insertE_ptr)(struct node *e, struct node *start) = &insertEvent;
		/* insertC_ptr is a pointer to function int insertCustomer(struct node *e, struct node *start) */		
    	int (*insertC_ptr)(struct node *e, struct node *start) = &insertCustomer;
		/* delete_ptr is a pointer to function int delete(struct node *start)*/
		int (*delete_ptr)(struct node *start) = &delete;
		/* findShortestQ_ptr is a pointer to function int findShortestQ(struct pair *array [], int length) */
		int (*findShortestQ_ptr)(struct pair *array [], int length) = &findShortestQ;

		/*Head node for the event queue*/
		struct node *event = malloc(sizeof(struct node));
		event->size = 0;
				
		if(i == 1){
			//printf("%s\n","Running the simulation for the case of multiple queues for multiple tellers");
			int customers = strtoint(argv[1]);
			int tellers = strtoint(argv[2]);
			float simulationTime = atof(argv[4]);
			float avgServiceTime = atof(argv[3]);

			/*Stores the time spent by each customer in an array*/
			float customerTimes [customers];

			/*Stores the maximum waiting time for the customers*/
			float maxWait = 0.0;

			/*Stores the number of customers served*/
			int customer = 0;

			/*Pointer to the array of tellerQueues and initializing the queues.*/
			struct pair *tellerQueues [tellers];
			for(int i = 0;i<tellers;i++){
				tellerQueues[i] = malloc(sizeof(struct pair));
				tellerQueues[i]->n = malloc(sizeof(struct node));
				tellerQueues[i]->n->end = NULL;
				tellerQueues[i]->n->next = NULL;
				tellerQueues[i]->n->type = malloc(sizeof(char));
				tellerQueues[i]->n->type = "T";
				tellerQueues[i] ->size = 0;
				tellerQueues[i]->n->time = GlobalTime;
				tellerQueues[i]->n->status = 0;
				tellerQueues[i]->n->numCustomers = 0;
				tellerQueues[i]->n->idleTime = 0.0;
				tellerQueues[i]->n->serviceTime = 0.0;
				tellerQueues[i]->n->id = i;
			}

			for(int i = 0;i<customers;i++){

				/*First creating the Customer-Arrival Events (CA) corresponding to every customer*/	
				/*A customer node to for the reference of the event node*/
				struct node *c = malloc(sizeof(struct node));
				c->end = NULL;
				c->next = NULL;
				c->type = malloc(sizeof(char));
				c->time = ((float)rand()/(float)(RAND_MAX)) * simulationTime; //Denotes the arrival time of c

				/*The event object to be inserted into the queue */
				struct node *e = malloc(sizeof(struct node));
				e->end = NULL;
				e->next = NULL;
				e->type = "CA";
				e->ref = c;
				e->time = c->time;

				int ns = insertEvent(e,event);
				int t = event->size;
			}	

		 /* Code for Processing the events */ 
			while(consumers < customers && event->next != NULL){
				consumers = 0;
				struct node *curr = event->next;

				if(strcmp(curr->type,"CA")==0){

					GlobalTime = curr->time;
					//int res = findShortestQ(tellerQueues,tellers);
					int res = findShortestQ_ptr(tellerQueues,tellers);
					//int ns = insertCustomer(curr->ref,tellerQueues[res]->n);
					int ns = insertC_ptr(curr->ref,tellerQueues[res]->n);

					tellerQueues[res]->size = ns;
					/*The reference for the customer would be its corresponding teller*/
					curr->ref->ref = tellerQueues[res]->n;
					delete_ptr(event);
					//delete(event);
				}
				else if(strcmp(curr->type,"CS")==0){
	
					GlobalTime = curr->time;
					float waitTime = GlobalTime - curr->ref->time;
					curr->ref->ref->serviceTime = curr->ref->ref->serviceTime + waitTime;
					curr->ref->ref->numCustomers++;
					assert(waitTime>=0);
					customerTimes[customer] = waitTime;
					customer++;
					//printf("Time spent by Customer: %f, Id of queue: %d, Size of Queue: %d\n",waitTime,curr->ref->ref->id,curr->ref->ref->size+1);
					//delete(event);
					delete_ptr(event);
				}
				else if(strcmp(curr->type,"TI")==0){
	
					GlobalTime = curr->time;
					//delete(event);
					delete_ptr(event);
					curr->ref->status = 0;
					/*If there are customers then set the status to 0, i.e start looking for the customer*/
					if(curr->ref->size > 0){
						curr->ref->status = 0;
					}
					/*If the line is empty, then remain idle. Creating a new idle event*/
					else{
						struct node *TI = malloc(sizeof(struct node));
						TI->type = "TI";
						TI->ref = curr->ref;
						float f = (rand()%150+1)/60;
						TI->time = GlobalTime + f;
						TI->ref->idleTime = TI->ref->idleTime + f;
						//insertEvent(TI,event);
						insertE_ptr(TI,event);
						curr->ref->status = 1;
					}
				}
				else{
					printf("Invalid Query!/n");
				}
				assert(GlobalTime == curr->time);
				for(int j = 0;j<tellers;j++){
					consumers = consumers + tellerQueues[j]->n->numCustomers;
					if(tellerQueues[j]->n->status == 0){
						if(tellerQueues[j]->size > 0){

							/*Creating new event of type Customer Serviced */
							struct node *ncs = malloc(sizeof(struct node));
							ncs->type = "CS";
							ncs->ref = tellerQueues[j]->n->next;
							//printf("Size: %d\n",tellerQueues[j]->size);
							ncs->time = GlobalTime + ((float)rand()/(float)(RAND_MAX)) * avgServiceTime *2;
							float wait = GlobalTime - tellerQueues[j]->n->next->time;
							assert(wait>=0);
							//printf("Wait1: %f\n",wait);
							if(wait>maxWait){
								maxWait = wait;
							}			
							//insertEvent(ncs,event);
							insertE_ptr(ncs,event);
							//int ns = delete(tellerQueues[j]->n);
							int ns = delete_ptr(tellerQueues[j]->n);							
							tellerQueues[j]->size = ns;

							/*Creating new event of type Teller Idle (Service Finished Precisely) */
							struct node *ti = malloc(sizeof(struct node));
							ti->type = "TI";
							ti->ref = tellerQueues[j]->n;
							tellerQueues[j]->n->status = 1;
							ti->time = ncs->time;
							//insertEvent(ti,event);
							insertE_ptr(ti,event);

						}
						else{
							/*Looking in other lines*/
							int del = 0;
							for(int k =0;k<tellers;k++){
								if(tellerQueues[k]->n->size>0){
									/*Creating new event of type Customer Serviced */
									struct node *ncs = malloc(sizeof(struct node));
									ncs->type = "CS";
									ncs->ref = tellerQueues[k]->n->next;
									float wait = GlobalTime - tellerQueues[k]->n->next->time;
									assert(wait>=0);
									//printf("Wait11: %f\n",wait);
									if(wait>maxWait){
										maxWait = wait;
									}
									ncs->time = GlobalTime + ((float)rand()/(float)(RAND_MAX)) * avgServiceTime *2;
									//insertEvent(ncs,event);
									insertE_ptr(ncs,event);
									//int ns = delete(tellerQueues[k]->n);
									int ns = delete_ptr(tellerQueues[k]->n);
									tellerQueues[k]->size = ns;

									/*Creating new event of type Teller Idle (Service Finished Precisely)*/ 
									struct node *ti = malloc(sizeof(struct node));
									ti->type = "TI";
									ti->ref = tellerQueues[j]->n;
									tellerQueues[j]->n->status = 1;
									ti->time = ncs->time;
									//insertEvent(ti,event);
									insertE_ptr(ti,event);
									del = 1;
									break;
								}
							}
							/*if(del==0){
								/*No customer in any line. Hence TI event.*/
								/*No new events to be created. 								
							}*/
						}
					}
				}
			}
			float servTime = 0.0;
			float idleTime = 0.0;
			for(int j = 0;j<tellers;j++){
				servTime = servTime + tellerQueues[j]->n->serviceTime;
				idleTime = idleTime + tellerQueues[j]->n->idleTime;
					//printf("Teller Id: %d\n",tellerQueues[j]->n->id);
					//printf("Number of customers served till now: %d\n",tellerQueues[j]->n->numCustomers);
					//printf("Total service time: %f\n",tellerQueues[j]->n->serviceTime);
					//printf("Total idle time: %f\n",tellerQueues[j]->n->idleTime);
					//printf("Avg service time per customer: %f\n",(tellerQueues[j]->n->serviceTime / (tellerQueues[j]->n->numCustomers)));
			}
			
			printf("Number of Tellers: %d\n",tellers);
			printf("Type of Queueing: Multiple Queues\n");
			printf("Total number of customers served: %d\n",customers);
			printf("Average time spent by a customer in the bank: %f   SD: %f\n",calculateMean(customerTimes),calculateSD(customerTimes));
			printf("Maximum waiting time: %f\n",maxWait);
			printf("Total teller service time: %f\n",servTime);
			printf("Total teller idle time: %f\n",idleTime);		
			printf("\n");
		}

		else{
			//printf("%s\n","Running the simulation for the case of single queue for multiple tellers");
			event->next = NULL;
			GlobalTime = 0;
			int customers = strtoint(argv[1]);
			int tellers = strtoint(argv[2]);
			float simulationTime = atof(argv[4]);
			float avgServiceTime = atof(argv[3]);
			int common = 0;

			/*Stores the time spent by each customer in an array*/
			float customerTimes [customers];

			/*Stores the maximum waiting time for the customers*/
			float maxWait = 0.0;

			/*Stores the number of customers served*/
			int customer = 0;

			/*Pointer to the array of tellerQueues and initializing the queues.*/
			struct pair *tellerQueues [tellers];
			for(int i = 0;i<tellers;i++){
				tellerQueues[i] = malloc(sizeof(struct pair));
				tellerQueues[i]->n = malloc(sizeof(struct node));
				tellerQueues[i]->n->end = NULL;
				tellerQueues[i]->n->next = NULL;
				tellerQueues[i]->n->type = malloc(sizeof(char));
				tellerQueues[i]->n->type = "T";
				tellerQueues[i] ->size = 0;
				tellerQueues[i]->n->time = GlobalTime;
				tellerQueues[i]->n->status = 0;
				tellerQueues[i]->n->numCustomers = 0;
				tellerQueues[i]->n->idleTime = 0.0;
				tellerQueues[i]->n->serviceTime = 0.0;
				tellerQueues[i]->n->id = i;
			}

			for(int i = 0;i<customers;i++){

				/*First creating the Customer-Arrival Events (CA) corresponding to every customer*/	
				/*A customer node to for the reference of the event node*/
				struct node *c = malloc(sizeof(struct node));
				c->end = NULL;
				c->next = NULL;
				c->type = malloc(sizeof(char));
				c->time = ((float)rand()/(float)(RAND_MAX)) * simulationTime; //Denotes the arrival time of c

				/*The event object to be inserted into the queue */
				struct node *e = malloc(sizeof(struct node));
				e->end = NULL;
				e->next = NULL;
				e->type = "CA";
				e->ref = c;
				e->time = c->time;
				//int ns = insertEvent(e,event);
				int ns = insertE_ptr(e,event);
				int t = event->size;
			}	

		 /* Code for Processing the events */ 
		    consumers = 0;
			while(consumers < customers && event->next != NULL){
				
				struct node *curr = event->next;

				if(strcmp(curr->type,"CA")==0){
					GlobalTime = curr->time;
					//int ns = insertCustomer(curr->ref,tellerQueues[common]->n);
					int ns = insertC_ptr(curr->ref,tellerQueues[common]->n);
					tellerQueues[common]->size = ns;
					/*The reference for the customer would be its corresponding teller*/
					curr->ref->ref = tellerQueues[common]->n;
					curr->ref->time = GlobalTime;
					//delete(event);
					delete_ptr(event);

				}
				else if(strcmp(curr->type,"CS")==0){
					GlobalTime = curr->time;
					float waitTime = GlobalTime - curr->ref->time;
					curr->ref->ref->serviceTime = curr->ref->ref->serviceTime + waitTime;
					curr->ref->ref->numCustomers++;
					customerTimes[customer] = waitTime;
					customer++;					
					//printf("Time spent by Customer: %f, Id of queue: %d, Size of Queue: %d\n",waitTime,curr->ref->ref->id,curr->ref->ref->size+1);
					//delete(event);
					delete_ptr(event);
				}
				else if(strcmp(curr->type,"TI")==0){
					GlobalTime = curr->time;
					delete(event);
					curr->ref->status = 0;
					/*If there are customers then set the status to 0, i.e start looking for the customer*/
					if(tellerQueues[common]->size > 0){
						curr->ref->status = 0;
					}
					/*If the common line is empty, then remain idle. Creating a new idle event*/
					else{
						struct node *TI = malloc(sizeof(struct node));
						TI->type = "TI";
						TI->ref = curr->ref;
						float f = (rand()%150+1)/60;
						TI->time = GlobalTime + f;
						TI->ref->idleTime = TI->ref->idleTime + f;
						//insertEvent(TI,event);
						insertE_ptr(TI,event);
						curr->ref->status = 1;
					}
				}
				else{
					printf("Invalid Query!/n");
				}
				consumers = 0;			
				for(int j = 0;j<tellers;j++){
					consumers = consumers + tellerQueues[j]->n->numCustomers;
					if(tellerQueues[j]->n->status == 0){
						if(tellerQueues[common]->size > 0){
							/*Creating new event of type Customer Serviced */
							struct node *ncs = malloc(sizeof(struct node));
							ncs->type = "CS";
							ncs->ref = tellerQueues[common]->n->next;
							ncs->time = GlobalTime + ((float)rand()/(float)(RAND_MAX)) * avgServiceTime *2;
							//insertEvent(ncs,event);
							ncs->ref->ref = tellerQueues[j]->n;
							float wait = GlobalTime - tellerQueues[common]->n->next->time;
							assert(wait>=0);
							if(wait>maxWait){
								maxWait = wait;
							}							
							insertE_ptr(ncs,event);
							//int ns = delete(tellerQueues[common]->n);	
							int ns = delete_ptr(tellerQueues[common]->n);							
							tellerQueues[common]->size = ns;
							/*Creating new event of type Teller Idle (Service Finished Precisely) */
							struct node *ti = malloc(sizeof(struct node));
							ti->type = "TI";
							ti->ref = tellerQueues[j]->n;
							tellerQueues[j]->n->status = 1;
							ti->time = ncs->time;
							insertE_ptr(ti,event);
						}
					}
				}								
			}
			float servTime = 0.0;
			float idleTime = 0.0;
			for(int j = 0;j<tellers;j++){
				servTime = servTime + tellerQueues[j]->n->serviceTime;
				idleTime = idleTime + tellerQueues[j]->n->idleTime;
					//printf("Teller Id: %d\n",tellerQueues[j]->n->id);
					//printf("Number of customers served till now: %d\n",tellerQueues[j]->n->numCustomers);
					//printf("Total service time: %f\n",tellerQueues[j]->n->serviceTime);
					//printf("Total idle time: %f\n",tellerQueues[j]->n->idleTime);
					//printf("Avg service time per customer: %f\n",(tellerQueues[j]->n->serviceTime / (tellerQueues[j]->n->numCustomers)));
			}
			printf("\n");
			printf("Number of Tellers: %d\n",tellers);
			printf("Type of Queueing: Single Queue\n");
			printf("Total number of customers served: %d\n",customers);
			printf("Average time spent by a customer in the bank: %f   SD: %f\n",calculateMean(customerTimes),calculateSD(customerTimes));
			printf("Maximum waiting time: %f\n",maxWait);
			printf("Total teller service time: %f\n",servTime);
			printf("Total teller idle time: %f\n",idleTime);
			fprintf(f,"%f  %d\n",calculateMean(customerTimes),tellers);
			printf("\n");
		}	
	}
	return 0;
}
