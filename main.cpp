#include <iostream>
#include <string>
using namespace std;

class Product {
private:
    int id;
    string name;
    double price;
public:
    Product(int idd, string namee, double pricee) {
        id = idd;
        name = namee;
        price = pricee;
    }
    virtual ~Product() {}
    virtual void display() {
        cout << " Product ID : " << id << endl;
        cout << " Name : " << name << endl;
        cout << " Price : " << price << " PKR" << endl;
    }
    double getPrice() { return price; }
    int getId() { return id; }
};

class Electronics : public Product {
private:
    int warranty;
public:
    Electronics(int idd, string namee, double pricee, int warrantyy)
        : Product(idd, namee, pricee) {
        warranty = warrantyy;
    }
    void display() {
        cout << " Electronics Item\n";
        Product::display();
        cout << " Warranty : " << warranty << " year(s)\n";
    }
};

class Clothing : public Product {
private:
    string size;
public:
    Clothing(int idd, string namee, double pricee, string sizee)
        : Product(idd, namee, pricee) {
        size = sizee;
    }
    void display() {
        cout << " Clothing Item\n";
        Product::display();
        cout << " Size : " << size << endl;
    }
};

class Grocery : public Product {
private:
    string expiry;
public:
    Grocery(int idd, string namee, double pricee, string expiryy)
        : Product(idd, namee, pricee) {
        expiry = expiryy;
    }
    void display() {
        cout << " Grocery Item\n";
        Product::display();
        cout << " Expiry : " << expiry << endl;
    }
};

class Cart {
private:
    struct Node {
        Product* data;
        Node* next;
    };
    Node* head;
public:
    Cart() { head = NULL; }
    ~Cart() {
        while (head != NULL) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void addItem(Product* p) {
        Node* n = new Node();
        n->data = p;
        n->next = NULL;
        if (head == NULL) head = n;
        else {
            Node* t = head;
            while (t->next != NULL) t = t->next;
            t->next = n;
        }
        cout << " Item added to cart\n";
    }
    void viewCart() {
        if (head == NULL) {
            cout << " Cart is empty\n";
            return;
        }
        Node* t = head;
        double total = 0;
        int i = 1;
        cout << "\n YOUR CART \n";
        while (t != NULL) {
            cout << "\nItem " << i++ << endl;
            t->data->display();
            cout << " Status: Pending\n";
            total += t->data->getPrice();
            t = t->next;
        }
        cout << "\n Total: " << total << " PKR\n";
    }
};

class Shop {
private:
    struct PNode {
        Product* data;
        PNode* next;
    };
    PNode* productHead;
    Cart cart;
public:
    Shop() { productHead = NULL; }
    ~Shop() {
        while (productHead != NULL) {
            PNode* temp = productHead;
            productHead = productHead->next;
            delete temp->data;
            delete temp;
        }
    }
    void addProduct(Product* p) {
        PNode* n = new PNode();
        n->data = p;
        n->next = NULL;
        if (productHead == NULL) productHead = n;
        else {
            PNode* t = productHead;
            while (t->next != NULL) t = t->next;
            t->next = n;
        }
    }
    void loadProducts() {
        addProduct(new Electronics(1, "Laptop", 50000, 1));
        addProduct(new Electronics(2, "Headphones", 2500, 1));
        addProduct(new Clothing(3, "T-Shirt", 1200, "M"));
        addProduct(new Clothing(4, "Jeans", 2000, "32"));
        addProduct(new Grocery(5, "Chocolate Box", 1500, "2026-06-30"));
        addProduct(new Grocery(6, "Cooking Oil (1L)", 2200, "2026-12-15"));
    }
    void showProducts() {
        PNode* t = productHead;
        cout << "\n AVAILABLE PRODUCTS\n";
        while (t != NULL) {
            t->data->display();
            cout << endl;
            t = t->next;
        }
    }
    void addToCart() {
        int id;
        cout << "Enter Product ID: ";
        cin >> id;
        PNode* t = productHead;
        while (t != NULL) {
            if (t->data->getId() == id) {
                cart.addItem(t->data);
                return;
            }
            t = t->next;
        }
        cout << "X Product not found\n";
    }
    void luckyDraw() {
        char userChar;
        char luckyChar = 'R';
        cout << "\n LUCKY DRAW \n";
        cout << "Choose one letter (A-Z): ";
        cin >> userChar;
        if (toupper(userChar) == luckyChar) {
            cout << "\n CONGRATULATIONS!\n";
            cout << "You won a FREE PRODUCT \n";
            cout << " Chocolate Box added for FREE!\n";
            cart.addItem(new Grocery(99, "FREE Chocolate Box", 0, "2026-12-31"));
        } else {
            cout << "\nX Better luck next time\n";
        }
    }
    void showMenu() {
        int choice;
        do {
            cout << "\n Welcome to Lucky-Mart\n";
            cout << "1. Show Products\n";
            cout << "2. Add to Cart\n";
            cout << "3. View Cart\n";
            cout << "4. Lucky Draw \n";
            cout << "5. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;
            if (choice == 1) showProducts();
            else if (choice == 2) addToCart();
            else if (choice == 3) cart.viewCart();
            else if (choice == 4) luckyDraw();
        } while (choice != 5);
        cout << " Thank you for shopping\n";
    }
};

int main() {
    Shop s;
    s.loadProducts();
    s.showMenu();
    return 0;
}
