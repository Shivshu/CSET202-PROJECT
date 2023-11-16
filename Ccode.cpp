#include <iostream>
#include <vector>
#include <string>

class User {
public:
    std::string username;
    std::string password;
    std::string fullName;
    std::vector<User*> connections;

    User(const std::string& uname, const std::string& pwd, const std::string& name)
        : username(uname), password(pwd), fullName(name) {}

    void addConnection(User* user) {
        connections.push_back(user);
    }

    void displayConnections() const {
        std::cout << "Connections for " << fullName << ":\n";
        for (const auto& connection : connections) {
            std::cout << connection->fullName << "\n";
        }
    }
};

class Post {
public:
    std::string content;
    User* author;

    Post(const std::string& text, User* author)
        : content(text), author(author) {}
};

class CareerWise {
private:
    std::vector<User> users;
    std::vector<Post> posts;
    User* currentUser;

public:
    void displayMenu() {
        std::cout << "---------------------\n";
        std::cout << "1. Register\n";
        std::cout << "2. Log In\n";
        std::cout << "3. Create a Post\n";
        std::cout << "4. View News Feed\n";
        std::cout << "5. View Connections\n";
        std::cout << "6. Exit\n";
        std::cout << "---------------------\n";
    }

    void run() {
        int choice;

        do {
            displayMenu();
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            switch (choice) {
                case 1:
                    handleRegistration();
                    break;
                case 2:
                    handleLogin();
                    break;
                case 3:
                    handlePostCreation();
                    break;
                case 4:
                    displayNewsFeed();
                    break;
                case 5:
                    displayConnections();
                    break;
                case 6:
                    std::cout << "Exiting CareerWise. Goodbye!\n";
                    break;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 6);
    }

    void handleRegistration() {
        std::string username, password, fullName;
        std::cout << "Enter username: ";
        std::cin >> username;
        std::cout << "Enter password: ";
        std::cin >> password;
        std::cout << "Enter full name: ";
        std::cin.ignore();  // Consume the newline character
        std::getline(std::cin, fullName);

        registerUser(username, password, fullName);
    }

    void handleLogin() {
        std::string username, password;
        std::cout << "Enter username: ";
        std::cin >> username;
        std::cout << "Enter password: ";
        std::cin >> password;

        loginUser(username, password);
    }

    void handlePostCreation() {
        std::string content;
        std::cout << "Enter your post: ";
        std::cin.ignore();  // Consume the newline character
        std::getline(std::cin, content);

        createPost(content);
    }

    bool registerUser(const std::string& username, const std::string& password, const std::string& fullName) {
        for (const auto& user : users) {
            if (user.username == username) {
                std::cout << "Username already exists. Please choose a different username.\n";
                return false;
            }
        }

        users.emplace_back(username, password, fullName);
        std::cout << "Registration successful.\n";
        return true;
    }

    bool loginUser(const std::string& username, const std::string& password) {
        for (auto& user : users) {
            if (user.username == username && user.password == password) {
                currentUser = &user;
                std::cout << "Login successful. Welcome, " << user.fullName << "!\n";
                return true;
            }
        }

        std::cout << "Invalid username or password. Please try again.\n";
        return false;
    }

    void createPost(const std::string& content) {
        if (currentUser != nullptr) {
            posts.emplace_back(content, currentUser);
            std::cout << "Post created successfully.\n";
        } else {
            std::cout << "Please log in to create a post.\n";
        }
    }

    void displayNewsFeed() const {
        std::cout << "News Feed:\n";
        for (const auto& post : posts) {
            std::cout << post.author->fullName << ": " << post.content << "\n";
        }
    }

    void displayConnections() const {
        if (currentUser != nullptr) {
            currentUser->displayConnections();
        } else {
            std::cout << "Please log in to view connections.\n";
        }
    }
};

int main() {
    CareerWise careerWise;
    careerWise.run();

    return 0;
}
