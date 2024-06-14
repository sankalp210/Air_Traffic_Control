#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct 
{
    int hrs;
    int min;
} TIME;

typedef struct FlightPlan
{
    int flightId;
    TIME departureTime;
    TIME eta;
    struct FlightPlan* next;
} FlightPlan;

typedef struct Bucket 
{
    int bucketId;
    TIME etaStart;
    TIME etaEnd;
    FlightPlan* flightPlans;
    struct Bucket* next;
} Bucket;

int timediff(TIME A, TIME B);
int maxtime(TIME A, TIME B) ;
Bucket* createBucket(int bucketId, TIME etaEnd, TIME etaStart);
FlightPlan* createFlightPlan(int flightId, TIME departureTime, TIME eta); 
void insertFlightPlan(Bucket **dashboard, FlightPlan *newFlightPlan);
void cancelFlightPlan(Bucket* dashboard, int flightId);
void showFlightStatus(Bucket* dashboard, int flightId); 
FlightPlan *mergeSortedLists(FlightPlan *l1, FlightPlan *l2);
void reArrangeBucket(Bucket **bucket, TIME t);
void Print(Bucket *bucket);


int timediff(TIME A, TIME B) 
{
    return (A.hrs - B.hrs) * 60 + (A.min - B.min);
}

int maxtime(TIME A, TIME B) 
{
    if (A.hrs == B.hrs && A.min == B.min)
        return 0;
    else if (A.hrs > B.hrs || (A.hrs == B.hrs && A.min > B.min))
        return -1;
    else
        return 1;
}

Bucket* createBucket(int bucketId, TIME etaEnd, TIME etaStart) 
{
    Bucket* new_bucket = (Bucket*)malloc(sizeof(Bucket));
    new_bucket->bucketId = bucketId;
    new_bucket->etaStart = etaStart;
    new_bucket->etaEnd = etaEnd;
    new_bucket->flightPlans = NULL;
    new_bucket->next = NULL;
    return new_bucket;
}

FlightPlan* createFlightPlan(int flightId, TIME departureTime, TIME eta) 
{
    FlightPlan* newFlightPlan = (FlightPlan*)malloc(sizeof(FlightPlan));
    newFlightPlan->flightId = flightId;
    newFlightPlan->departureTime = departureTime;
    newFlightPlan->eta = eta;
    newFlightPlan->next = NULL;
    return newFlightPlan;
}

void insertFlightPlan(Bucket **dashboard, FlightPlan *newFlightPlan)
{
    Bucket *temp = *dashboard;                //sorted by eta interval
    Bucket *prev;
    while(temp->etaStart.hrs < newFlightPlan->eta.hrs )
    {
        temp = temp->next;
    }
    if(temp->etaStart.hrs == newFlightPlan->eta.hrs)
    {
        if(temp->flightPlans == NULL)        
        {
            temp->flightPlans = newFlightPlan;
        }
        else
        {
            FlightPlan *curr = temp->flightPlans;        //sorted by departure time
            FlightPlan *prev = NULL;
			
			//insertAtBeggining
            if(!curr || curr->departureTime.hrs > newFlightPlan->departureTime.hrs || (curr->departureTime.hrs == newFlightPlan->departureTime.hrs && curr->departureTime.min > newFlightPlan->departureTime.min))
            {
                newFlightPlan->next = curr;
                temp->flightPlans = newFlightPlan;
            }
            else   //insertAtIndex
            {
                while(curr && (curr->departureTime.hrs < newFlightPlan->departureTime.hrs || (curr->departureTime.hrs == newFlightPlan->departureTime.hrs && curr->departureTime.min < newFlightPlan->departureTime.min)))
                {
                    prev = curr;
                    curr = curr->next;
                }

                newFlightPlan->next = curr;
                if(prev)
                    prev->next = newFlightPlan;
                else
                    temp->flightPlans = newFlightPlan;         //beggining
            }

        }
    }

    
}

void cancelFlightPlan(Bucket* dashboard, int flightId) 
{
    Bucket* currBucket = dashboard;
    while (currBucket != NULL) 
    {
        FlightPlan* prev = NULL;
        FlightPlan* curr = currBucket->flightPlans;
        while (curr != NULL && curr->flightId != flightId) 
        {
            prev = curr;
            curr = curr->next;
        }

        if (curr != NULL) 
        {
            if (prev == NULL)      //deleteAtBeggining
            {
                currBucket->flightPlans = curr->next;
                
            } else             //deleteAtIndex
            {
                prev->next = curr->next;
            }
            free(curr);
            break;
        }

        currBucket = currBucket->next;
    }
}

void showFlightStatus(Bucket* dashboard, int flightId) 
{
    Bucket* currBucket = dashboard;
    while (currBucket != NULL) 
    {
        FlightPlan* curr = currBucket->flightPlans;
        while (curr != NULL && curr->flightId != flightId) 
        {
            curr = curr->next;
        }

        if (curr != NULL) 
        {
            printf("Flight ID: %d\n", curr->flightId);
            printf("Departure Time: %d:%d\n", curr->departureTime.hrs, curr->departureTime.min);
            printf("ETA: %d:%d\n", curr->eta.hrs, curr->eta.min);
            return;
        }

        currBucket = currBucket->next;
    }

    printf("Flight ID %d not found.\n", flightId);
}

FlightPlan *mergeSortedLists(FlightPlan *l1, FlightPlan *l2)
{
    TIME notTime;
    notTime.hrs = -1;
    notTime.min = -1;
    FlightPlan *dummy = createFlightPlan(-1, notTime, notTime);
    FlightPlan *current = dummy;

    while (l1 != NULL && l2 != NULL)
    {
        if (l1->departureTime.hrs < l2->departureTime.hrs)
        {
            current->next = l1;
            l1 = l1->next;
        }
        else if (l1->departureTime.hrs == l2->departureTime.hrs)
        {
            if (l1->departureTime.min < l2->departureTime.min)
            {
                current->next = l1;
                l1 = l1->next;
            }
            else
            {
                current->next = l2;
                l2 = l2->next;
            }
        }
        else
        {
            current->next = l2;
            l2 = l2->next;
        }
        current = current->next;
    }

    // If one of the lists is longer than the other or if either of the list is empty
    if (l1 != NULL)
    {
        current->next = l1;
    }
    else
    {
        current->next = l2;
    }
    FlightPlan *ans = dummy->next;
    free(dummy);
    return ans;
}

void reArrangeBucket(Bucket **bucket, TIME t)
{
    TIME notTime;
    notTime.hrs = -1;
    notTime.min = -1;
    Bucket *tempBucket = createBucket(-1, notTime, notTime);
    Bucket *curr = *bucket;
    Bucket *prev = NULL;
    Bucket *start;
    

    if (t.hrs == 0 && t.min == 0)
    {
        printf("!! Original Time Interval !!\n");
    }
    else
    {
        while (curr)
        {
            curr->etaStart.min = t.min;
            curr->etaEnd.hrs = (curr->etaStart.hrs+1) % 24;
            curr->etaEnd.min = t.min - 1;
            FlightPlan *temp = curr->flightPlans;
            FlightPlan *dummy = createFlightPlan(-11, notTime, notTime);
            FlightPlan *dummyTail = dummy;
            FlightPlan *store = createFlightPlan(-1, notTime, notTime), *storeTail = store;
            while (temp)
            {
                FlightPlan *next = temp->next;
                if (temp->eta.min >= t.min)
                {
                    dummyTail->next = temp;
                    dummyTail = dummyTail->next;
                }
                else
                {
                    if (storeTail == NULL)
                    {
                        storeTail = temp;
                        store = storeTail;
                    }
                    else
                    {
                        storeTail->next = temp;
                        storeTail = storeTail->next;
                    }
                }
                temp->next = NULL;
                temp = next;
            }
            // adding data to previous bucket
            curr->flightPlans = NULL;
            curr->flightPlans = dummy->next;
            if (prev == NULL)
            {
                tempBucket->flightPlans = store->next;
            }
            else
            {
                FlightPlan *l1 = prev->flightPlans;
                FlightPlan *l2 = store->next;
                prev->flightPlans = mergeSortedLists(l1, l2);
            }
            if (curr->next == NULL)
            {
                FlightPlan *l1 = curr->flightPlans;
                FlightPlan *l2 = tempBucket->flightPlans;
                curr->flightPlans = mergeSortedLists(l1, l2);
            }
            prev = curr;
            curr = curr->next;
        }
        // changing *bucket
        Bucket *Start = *bucket;
        Bucket *current = *bucket;
        Bucket *previous = NULL;
        if (t.hrs != 0)
        {
            while (current->etaStart.hrs < t.hrs)
            {
                previous = current;
                current = current->next;
            }
            *bucket = current;
            previous->next = NULL;
            current = (*bucket)->next;
            while (current->next)
            {
                current = current->next;
            }
            current->next = Start;
        }
    }
}

void Print(Bucket *bucket)
{
    Bucket *temp = bucket;
    while (temp)
    {
        printf("\n");
        printf("Bucket Id: %d\n", temp->bucketId);
        printf("ETA Start: %d:%d\n", temp->etaStart.hrs, temp->etaStart.min);
        printf("ETA End: %d:%d\n", temp->etaEnd.hrs, temp->etaEnd.min);
        FlightPlan *temp2 = temp->flightPlans;
        while (temp2)
        {
            printf("Flight Id: %d\n", temp2->flightId);
            printf("Departure Time: %d:%d\n", temp2->departureTime.hrs, temp2->departureTime.min);
            printf("ETA: %d:%d\n", temp2->eta.hrs, temp2->eta.min);
            temp2 = temp2->next;
        }
        temp = temp->next;
        printf("\n");
    }
}


static int Id = 500;
int main() 
{
    Bucket* dashboard = NULL;

    // Sample usage
    TIME current_time = {4, 30};
    int choice;
    Bucket *temp;
    temp = dashboard;

    for (int i = 0; i < 24; i++) 
    {
        Bucket* newBucket = malloc(sizeof(Bucket));
        newBucket->bucketId = Id + i;
        newBucket->etaStart.hrs = i;
        newBucket->etaStart.min = 0;
        newBucket->etaEnd.hrs = i + 1;
        newBucket->etaEnd.min = 0;
        newBucket->flightPlans = NULL;   // Initially, no flight plans
        newBucket->next = NULL;

        // Link the new bucket to the existing list
        if(temp != NULL)
        {
            temp->next = newBucket;
            temp = temp->next;   
        }
        else if(temp == NULL)
        {
            temp = newBucket;
            dashboard = temp;
        }
    }

   FILE *input_file = fopen("input.txt", "r");
    if (input_file == NULL) 
    {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }
    // Sample flight plans

     int flightPlans[200][5];
    for (int i = 0; i < 200; i++) 
    {
        if (fscanf(input_file, "%d %d %d %d %d", 
                   &flightPlans[i][0], &flightPlans[i][1], &flightPlans[i][2], 
                   &flightPlans[i][3], &flightPlans[i][4]) != 5) 
        {
            fprintf(stderr, "Error reading flight plan %d from input file\n", i + 1);
            fclose(input_file);
            return EXIT_FAILURE;
        }
    }

    // Insert flight plans into the dashboard
    for (int i = 0; i < 200; i++) 
    {
        TIME ETA;
        TIME Depart;
        ETA.hrs = flightPlans[i][3];
        ETA.min = flightPlans[i][4];
        Depart.hrs = flightPlans[i][1];
        Depart.min = flightPlans[i][2];
        FlightPlan *a = createFlightPlan(flightPlans[i][0],Depart,ETA);
        insertFlightPlan(&dashboard,a);

    }

    printf("\n");
    Print(dashboard);
    while (1) 
    {
        printf("\n1. Insert a new flight plan\n");
        printf("2. Cancel a flight plan\n");
        printf("3. Show flight status\n");
        printf("4. Show flight plans within next hour\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1: 
            {
                int bucket_id, flight_id, dep_hour, dep_min, eta_hour, eta_min;
                printf("Enter flight ID: ");
                scanf("%d", &flight_id);
                printf("Enter departure time (hh:mm): ");
                scanf("%d %d", &dep_hour, &dep_min);
                printf("Enter ETA (hh:mm): ");
                scanf("%d %d", &eta_hour, &eta_min);
                TIME departureTime = {dep_hour, dep_min};
                TIME eta = {eta_hour, eta_min};
                FlightPlan* new_flight_plan = createFlightPlan(flight_id, departureTime, eta);
                if (dashboard == NULL) 
                {
                    TIME start_time = {dep_hour, 0};
                    TIME end_time = {start_time.hrs + 1, 0};
                    dashboard = createBucket(bucket_id, start_time, end_time);
                }
                insertFlightPlan(&dashboard, new_flight_plan);
                Print(dashboard);
                break;
            }
            case 2: 
            {
                int flight_id;
                printf("Enter flight ID to cancel: ");
                scanf("%d", &flight_id);
                cancelFlightPlan(dashboard, flight_id);
                Print(dashboard);
                break;
            }
            case 3: 
            {
                int flight_id;
                printf("Enter flight ID to show status: ");
                scanf("%d", &flight_id);
                showFlightStatus(dashboard, flight_id);
                break;
            }
            case 4: 
            {   int current_hour, current_minute;
                 printf("Enter current time (hh:mm): ");
                scanf("%d %d", &current_hour, &current_minute);
               TIME current_time = {current_hour, current_minute};

                printf("Showing flight plans within next hour:\n");
               
                reArrangeBucket(&dashboard, current_time);

                Print(dashboard);
                break;
            }
            case 5: 
            {
                // Free allocated memory
                while (dashboard != NULL) 
                {
                    Bucket* temp = dashboard;
                    dashboard = dashboard->next;
                    FlightPlan* current_flight = temp->flightPlans;
                    while (current_flight != NULL) {
                        FlightPlan* temp_flight = current_flight;
                        current_flight = current_flight->next;
                        free(temp_flight);
                    }
                    free(temp);
                }
                return 0;
            }
            default: 
            {
                printf("Invalid choice! Please enter a valid option.\n");
                break;
            }
        }
    }

    return 0;
}
