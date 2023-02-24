#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include "customer.h"
#include "order.h"

using namespace std;

const string CUSTOMERS_FILE = "customers.bin";
const string ORDERS_FILE = "orders.bin";

void add_customer(vector<Customer>& customers);
void add_order(vector<Order>& orders, const vector<Customer>& customers);
void update_customer(vector<Customer>& customers);
void update_order(vector<Order>& orders, const vector<Customer>& customers);
void delete_customer(vector<Customer>& customers, vector<Order>& orders);
void delete_order(vector<Order>& orders);
void list_customers(const vector<Customer>& customers);
void list_orders(const vector<Order>& orders);

int main() {

    vector<Customer> customers;
    vector<Order> orders;

    ifstream customers_input(CUSTOMERS_FILE, ios::binary);
    if (customers_input) {
        while (customers_input) {
            Customer customer;
            customer.read(customers_input);
            if (customers_input) {
                customers.push_back(customer);
            }
        }
    }

    ifstream orders_input(ORDERS_FILE, ios::binary);
    if (orders_input) {
        while (orders_input) {
            Order order;
            order.read(orders_input);
            if (orders_input) {
                orders.push_back(order);
            }
        }
    }

    int choice;
    do {
        cout << "\n1. Add customer\n";
        cout << "2. Add order\n";
        cout << "3. Update customer\n";
        cout << "4. Update order\n";
        cout << "5. Delete customer\n";
        cout << "6. Delete order\n";
        cout << "7. List customers\n";
        cout << "8. List orders\n";
        cout << "9. Exit\n";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                add_customer(customers);
                break;
            case 2:
                add_order(orders, customers);
                break;
            case 3:
                update_customer(customers);
                break;
            case 4:
                update_order(orders, customers);
                break;
            case 5:
                delete_customer(customers, orders);
                break;
            case 6:
                delete_order(orders);
                break;
            case 7:
                list_customers(customers);
                break;
            case 8:
                list_orders(orders);
                break;
            case 9:
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "Invalid choice. Please try again.\n";
                break;
            }

        } while (choice != 9);


    ofstream customers_output(CUSTOMERS_FILE, ios::binary);
    if (customers_output) {
        for (const auto &customer: customers) {
            customer.write(customers_output);
        }
    }

    ofstream orders_output(ORDERS_FILE, ios::binary);
        if (orders_output) {
            for (const auto &order: orders) {
                order.write(orders_output);
            }
        }

    return 0;
}

void add_customer(vector<Customer>& customers) {

    Customer customer;

    cout << "\nEnter customer id: ";
    cin >> customer.id_;
    cout << "Enter customer name: ";
    cin >> customer.name_;
    cout << "Enter customer email: ";
    cin >> customer.email_;
    cout << "Enter customer phone: ";
    cin >> customer.phone_;
    cout << "Enter customer address: ";
    cin >> customer.address_;

    customers.push_back(customer);

    cout << "\nCustomer added successfully.\n";
}
void add_order(vector<Order>& orders, const vector<Customer>& customers) {

    Order order;

    cout << "\nEnter order id: ";
    cin >> order.id_;
    cout << "Enter customer id: ";
    cin >> order.customer_id_;
    auto customer_iter = find_if(customers.begin(), customers.end(),
                                 [&order](const Customer &customer) {
                                            return customer.id_ == order.customer_id_;});
    if (customer_iter == customers.end()) {
        cout << "\nCustomer not found. Order not added.\n";
        return;
    }

    cout << "\nEnter item: ";
    cin >> order.item_;
    cout << "Enter quantity: ";
    cin >> order.quantity_;
    cout << "Enter order date (DD/MM/YYYY): ";
    cin >> order.order_date_;
    cout << "Enter delivery date (DD/MM/YYYY): ";
    cin >> order.delivery_date_;

    orders.push_back(order);

    cout << "\nOrder added successfully.\n";
}

void update_customer(vector<Customer>& customers) {

    int id;

    cout << "\nEnter customer id to update: ";
    cin >> id;
    auto customer_iter = find_if(customers.begin(), customers.end(),
                                      [id](const Customer& customer) {
                                          return customer.id_ == id;
                                      });
    if (customer_iter == customers.end()) {
        cout << "\nCustomer not found. Update failed.\n";
        return;
    }

    cout << "\nEnter new customer name: ";
    string name;
    getline(cin >> ws, name);
    if (!name.empty()) {
        customer_iter->name_ = name;
    }

    cout << "Enter new customer email: ";
    string email;
    getline(cin >> ws, email);
    if (!email.empty()) {
        customer_iter->email_ = email;
    }

    cout << "Enter new customer phone: ";
    string phone;
    getline(cin >> ws, phone);
    if (!phone.empty()) {
        customer_iter->phone_ = phone;
    }

    cout << "Enter new customer address: ";
    string address;
    getline(cin >> ws, address);
    if (!address.empty()) {
        customer_iter->address_ = address;
    }
    cout << "\nCustomer updated successfully.\n";
}
void update_order(vector<Order>& orders, const vector<Customer>& customers) {

    int id;
    cout << "\nEnter order id to update: ";
    cin >> id;
    auto order_iter = find_if(orders.begin(), orders.end(),
                                   [id](const Order& order) {
                                       return order.id_ == id;
                                   });
    if (order_iter == orders.end()) {
        cout << "\nOrder not found. Update failed.\n";
        return;
    }
    cout << "\nEnter new customer id: ";
    int customer_id;
    string input;
    getline(cin >> ws, input);
    if (!input.empty()) {
        customer_id = stoi(input);
        auto customer_iter = find_if(customers.begin(), customers.end(),
                                          [customer_id](const Customer& customer) {
                                              return customer.id_ == customer_id;
                                          });
        if (customer_iter == customers.end()) {
            cout << "\nCustomer not found. Update failed.\n";
            return;
        }
        order_iter->customer_id_ = customer_id;
    }
    cout << "\nEnter new item: ";
    getline(cin >> ws, input);
    if (!input.empty()) {
        order_iter->item_ = input;
    }
    cout << "Enter new quantity: ";
    getline(cin >> ws, input);
    if (!input.empty()) {
        order_iter->quantity_ = stoi(input);
    }
    cout << "Enter new order date (DD/MM/YYYY): ";
    getline(cin >> ws, input);
    if (!input.empty()) {
        order_iter->order_date_ = input;
    }
    cout << "Enter new delivery date (DD/MM/YYYY): ";
    getline(cin >> ws, input);
    if (!input.empty()) {
        order_iter->delivery_date_ = input;
    }
    cout << "\nOrder updated successfully.\n";
    }

void delete_customer(vector<Customer>& customers, vector<Order>& orders) {

    int id;
    cout << "\nEnter customer id to delete: ";
    cin >> id;
    auto customer_iter = find_if(customers.begin(), customers.end(),
                                      [id](const Customer& customer) {
                                          return customer.id_ == id;
                                      });
    if (customer_iter == customers.end()) {
        cout << "\nCustomer not found. Deletion failed.\n";
        return;
    }

    orders.erase(remove_if(orders.begin(), orders.end(),
                                [id](const Order& order) {
                                    return order.customer_id_ == id;
                                }), orders.end());

    customers.erase(customer_iter);
    cout << "\nCustomer deleted successfully.\n";
}
void delete_order(vector<Order>& orders) {

    int id;
    cout << "\nEnter order id to delete: ";
    cin >> id;
    auto order_iter = find_if(orders.begin(), orders.end(),
                                   [id](const Order& order) {
                                       return order.id_ == id;
                                   });
    if (order_iter == orders.end()) {
        cout << "\nOrder not found. Deletion failed.\n";
        return;
    }
    orders.erase(order_iter);
    cout << "\nOrder deleted successfully.\n";
}

void list_customers(const vector<Customer>& customers) {

    if (customers.empty()) {
        cout << "\nNo customers found!\n" << endl;
    } else{
        for (const auto& customer : customers) {
            cout << "\nCustomer ID: " << customer.id_ << endl;
            cout << "Name: " << customer.name_ << endl;
            cout << "Email: " << customer.email_ << endl;
            cout << "Phone: " << customer.phone_ << endl;
            cout << "Address: " << customer.address_ << endl;
        }
    }


}
void list_orders(const vector<Order>& orders) {

    if (orders.empty()) {
        cout << "\nNo orders found for this customer!\n" << endl;
    } else {
        for (const auto& order : orders) {
            cout << "\nOrder ID: " << order.id_ << endl;
            cout << "Customer ID: " << order.customer_id_ << endl;
            cout << "Item: " << order.item_ << endl;
            cout << "Quantity: " << order.quantity_ << endl;
            cout << "Order Date: " << order.order_date_ << endl;
            cout << "Delivery Date: " << order.delivery_date_ << endl;
        }
    }
}
