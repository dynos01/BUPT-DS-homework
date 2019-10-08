/*
 * License: GPLv3
 * BUPT DS homework: singly linked list with header node
 * Tested under G++ 9.2.0, with minimal parameters
 * Author: Yinuo Deng <i@dyn.im>
 * Last modified: Tue 08 Oct 2019 23:51:25 PM CST
*/

#include <iostream>

typedef struct Node {
    int data;
    Node *next;
} Node;

Node *temp = NULL, *prev = NULL, *head = new Node();

void tolower(std::string&);
void createNode(int);
void deleteNode(int);
Node* revertList(Node*);
void dumpList(void);
void verifyOrder(void);
int calcSum(void);
void destroyList(void);

int main(void) {
    std::string input;
    int data;
    bool created = false;
    while(true) {
        std::cin >> input;
        tolower(input);
        if(input == "create") {
            if(created) {
                std::cerr << "You have already created a list. " << std::endl;
                continue;
            }
            created = true;
            head->data = 0;
        }
        else if(input == "insert") {
            if(!created) {
                std::cerr << "Please execute \"create\" first. " << std::endl;
                continue;
            }
            std::cin >> data;
            createNode(data);
        }
        else if(input == "delete") {
            if(!created) {
                std::cerr << "Please execute \"create\" first. " << std::endl;
                continue;
            }
            std::cin >> data;
            deleteNode(data);
        }
        else if(input == "revert") {
            if(!created) {
                std::cerr << "Please execute \"create\" first. " << std::endl;
                continue;
            }
            head->next = revertList(head->next);
        }
        else if(input == "dump") {
            if(!created) {
                std::cerr << "Please execute \"create\" first. " << std::endl;
                continue;
            }
            dumpList();
        }
        else if(input == "verify") {
            if(!created) {
                std::cerr << "Please execute \"create\" first. " << std::endl;
                continue;
            }
            verifyOrder();
        }
        else if(input == "count") {
            if(!created) {
                std::cerr << "Please execute \"create\" first. " << std::endl;
                continue;
            }
            std::cout << head->data << std::endl;
        }
        else if(input == "sum") {
            if(!created) {
                std::cerr << "Please execute \"create\" first. " << std::endl;
                continue;
            }
            std::cout << calcSum() << std::endl;
        }
        else if(input == "destroy") {
            if(!created) {
                std::cerr << "Please execute \"create\" first. " << std::endl;
                continue;
            }
            created = false;
            destroyList();
        }
        else if(input == "bye") goto exit;
        else {
            std::cerr << "Invalid input. " << std::endl;
            continue;
        }
    }
exit:
    return 0;
}

void tolower(std::string &str) {
    for(size_t i = 0; i < str.length(); i++) str[i] = (str[i] >= 'A' && str[i] <= 'Z') ? str[i] + 'a' - 'A' : str[i];
}

void createNode(int data) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    if(newNode == NULL) {
        std::cerr << "Unable to create a new node. " << std::endl;
        return;
    }
    head->data++;
    newNode->data = data;
    temp = head;
    while(temp->next != NULL) {
        if(temp->next->data >= data) {
            newNode->next = temp->next;
            temp->next = newNode;
            return;
        }
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->next = NULL;
}

void deleteNode(int data) {
    temp = head->next;
    prev = head;
    while(temp != NULL) {
        if(temp->data == data) {
            prev->next = temp->next;
            free(temp);
            temp = prev->next;
            head->data--;
        }
        else {
            prev = temp;
            temp = temp->next;
        }
    }
}

Node* revertList(Node* head) {
    if(head == NULL || head->next == NULL) return head;
    else {
        temp = revertList(head->next);
        head->next->next = head;
        head->next = NULL;
        return temp;
    }
}

void dumpList(void) {
    int count = head->data;
    temp = head->next;
    if(!count) return;
    while(count > 1) {
        std::cout << temp->data << ", ";
        temp = temp->next;
        count--;
    }
    std::cout << temp->data << std::endl;
}

void verifyOrder(void) {
    temp = head->next;
    int tempData = temp->data;
    while(temp->next != NULL) {
        temp = temp->next;
        if(tempData > temp->data) {
            std::cout << "False" << std::endl;
            return;
        }
        tempData = temp->data;
    }
    std::cout << "True" << std::endl;
}

int calcSum(void) {
    int sum = 0, count = head->data;
    temp = head->next;
    while(count > 0) {
        sum += temp->data;
        temp = temp->next;
        count--;
    }
    return sum;
}

void destroyList(void) {
    temp = head->next;
    while(temp != NULL) {
        prev = temp->next;
        free(temp);
        temp = prev;
    }
}
