//
// Created by Yigit Sen on 27/10/2022.
//

#include "BST_Mailman.h"

// TODO: Constructors and Destructors
BST_Mailman::BST_Mailman()
{
    root = nullptr;
}

BST_Mailman_Node::BST_Mailman_Node(Mail *mail)
{
    streetName = mail->getStreetName();
    BST_Mailman_Node::addMail(mail);
    right = nullptr;
    left = nullptr;
}

BST_Mailman::~BST_Mailman()
{
    if(root) delete root;
}
BST_Mailman_Node::~BST_Mailman_Node()
{
    if(left) delete left;
    if(right) delete right;
}

// TODO: Getters
std::string BST_Mailman_Node::getStreetName() const
{
    return streetName;
}

BST_Mailman * BST_Mailman_Node::getRightBST() const
{
    return right;
}

BST_Mailman * BST_Mailman_Node::getLeftBST() const
{
    return left;
}


// TODO add mail to the array mailPtr[] - NOTE: WE WILL NEVER ASK YOU TO
//  PUT TOO MANY MAILS. (a max of MAX_NUM_MAILS add_mail calls)
void BST_Mailman::addMail(Mail *mail)
{   
    if(!root)
    {
        //std::cout << "root!: BST_Mailman::addMail" << std::endl;
        root = new BST_Mailman_Node(mail);
        return;
    }
    if(mail->getStreetName() == root->streetName)
    {
        root->addMail(mail);
    }
    if(mail->getStreetName() < root->streetName)  // go left
    {
        if(root->left)
        {
            root->left->addMail(mail);
        }
        else
        {
            root->left = new BST_Mailman();
            //root->left->root = new BST_Mailman_Node(mail);
            root->left->addMail(mail);
            //return;
        }
    }
    if(mail->getStreetName() > root->streetName)  // go left
    {
        if(root->right)
        {
            root->right->addMail(mail);
        }
        else
        {
            root->right = new BST_Mailman();
            //root->right->root = new BST_Mailman_Node(mail);
            root->right->addMail(mail);
            //return;
        }
    }
}

void BST_Mailman_Node::addMail(Mail *mail)
{
    if(currentMailsStored < MAX_NUM_MAILS)
    {
        //std::cout << "addmail BST_Mailman_Node successful" << std::endl;
        mailPtr[currentMailsStored] = mail;
        currentMailsStored++;
    }
}

// TODO: Remove a mail, given its street name and ID
bool BST_Mailman::remove(int id, std::string streetName)
{
    if(!root)
    {
        return false;
    }
    if(streetName < root->streetName)
    {
        if(root->left)
        {
            return root->left->remove(id, streetName);
        }
    }
    if(root->streetName < streetName)
    {
        if(root->right)
        {
            return root->right->remove(id, streetName);
        }
    }
    //when 
    return root->remove(id);
}

bool BST_Mailman_Node::remove(int id)
{
    for(int i = 0; i < currentMailsStored; i++)
    {
        if(mailPtr[i]->getId() == id)
        {
            delete mailPtr[i];
            return true;
        }
    }
    return false;
}

// TODO: Find a mail item, given its street name and ID
Mail * BST_Mailman::find(int id, std::string streetName)
{
    if(!root)
    {
        return nullptr;
    }
    if(streetName < root->streetName)
    {
        if(root->left)
        {
            return root->left->find(id, streetName);
        }
    }
    if(root->streetName < streetName)
    {
        if(root->right)
        {
            return root->right->find(id, streetName);
        }
    }
    return root->find(id);
    /*if(root->streetName == streetName)
    {
        return root->find(id);
    }
    return (streetName < root->streetName) ? root->left->find(id, streetName) : root->right->find(id, streetName);*/
}

Mail *BST_Mailman_Node::find(int id)
{
    for(int i = 0; i < currentMailsStored; i++)
    {
        if(mailPtr[i]->getId() == id)
        {
            return mailPtr[i];
        }
    }
    return nullptr;
}


// TODO: Print functions. See example outputs for the necessary formats.
void BST_Mailman::printInOrder() const
{
    if(!root)
    {
        return;
    }
    if(root)
    {
       //std::cout << "BST_Mailman::printInOrder() successful" << std::endl;
        if(root->left)
        {
            root->left->printInOrder();
        }
        //std::cout << "BST_Mailman::printInOrder()printing" << std::endl;
        root->print();
        if(root->right)
        {
            root->right->printInOrder();
        }
    }
}

void BST_Mailman::printPostOrder() const
{
    if(!root)
    {
        return;
    }
    if(root)
    {
        if(root->left)
        {
            root->left->printPostOrder();
        }
        if(root->right)
        {
            root->right->printPostOrder();
        }
        root->print();
    }
}

void BST_Mailman::printPreOrder() const
{
    if(!root)
    {
        return;
    }
    if(root)
    {
        root->print();
        if(root->left)
        {
            root->left->printPreOrder();
        }
        if(root->right)
        {
            root->right->printPreOrder();
        }

    }
}

void BST_Mailman_Node::print() const
{
    std::cout << "BST Node for Street: " << streetName << std::endl;
    for (int i = 0; i < currentMailsStored; ++i) {
        if(mailPtr[i] != nullptr)
        {
            mailPtr[i]->printMail();
        }
    }
}
