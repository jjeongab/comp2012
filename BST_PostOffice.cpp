//
// Created by Yigit Sen on 27/10/2022.
//

#include "BST_PostOffice.h"

// TODO: Constructors and Destructors

//TIP: root will be nullptr at first, and we'll add a node once we try to add a mail object.
BST_PostOffice::BST_PostOffice() 
{
    root = nullptr;
}

BST_PostOffice_Node::BST_PostOffice_Node(Mail *mail)
{
    district = mail->getDistrict();
    left = nullptr;
    right = nullptr;
    addMail(mail);

}

BST_PostOffice::~BST_PostOffice()
{
    if(root) delete root;
}

BST_PostOffice_Node::~BST_PostOffice_Node()
{
    if(left) delete left;
    if(right) delete right;
}

// TODO: Accessor functions.
BST_PostOffice * BST_PostOffice_Node::getLeftBST() const
{
    return left;
}

BST_PostOffice * BST_PostOffice_Node::getRightBST() const
{
    return right;
}

District BST_PostOffice_Node::getDistrict() const
{
    return district;
}


//TODO: Given a district, id and street name, find the mail object.
Mail *BST_PostOffice::find(District dist, int id, std::string streetName)
{
    if(!root)
    {
        return nullptr;
    }
    /*if(root->district == dist)
    {
        root->find(id, streetName);
    }*/
    if(dist < root->district)
    {
        //std::cout << "when dist < root->district" << std::endl;
        if(root->left)
        {
            return root->left->find(dist, id, streetName);
        }
        return nullptr;
    }
    if(root->district < dist)
    {
        //std::cout << "when dist >root->district" << std::endl;
        if(root->right)
        {
            return root->right->find(dist, id, streetName);
        }
        return nullptr;
    }
    //std::cout << "when dist == root->district" << std::endl;
    return root->find(id, streetName);
    //return (dist < root->district) ? root->left->find(dist, id, streetName) : root->right->find(dist, id, streetName);
}

Mail *BST_PostOffice_Node::find(int id, std::string streetName)
{
    for(int i = 0; i < HASH_MODULO; i++)
    {
        //std::cout << "find(id, stringName): " << std::endl;
        if(mailman[i].find(id, streetName))
        {
            //std::cout << "when it is true" << std::endl;
            return mailman[i].find(id, streetName);
        }
    }
    return nullptr;
}


// TODO: Given a district, id and street name, remove the mail object from the
// system.
bool BST_PostOffice::remove(District dist, int id, std::string streetName)
{
    if(!root)
    {
        return false;
    }
    if(dist < root->district)
    {
        if(root->left)
        {
            return root->left->remove(dist, id, streetName);
        }
        return false;
    }
    if(root->district < dist)
    {
        if(root->right)
        {
            return root->right->remove(dist, id, streetName);
        }
        return false;
    }
    return root->remove(id, streetName);
}

bool BST_PostOffice_Node::remove(int id, std::string streetName)
{
    for(int i = 0; i < HASH_MODULO; i++)
    {
        if(mailman[i].find(id, streetName))
        {
            return mailman[i].remove(id, streetName);
        }
    }
    return false;
}

// TODO: Add mail to the system
void BST_PostOffice::addMail(Mail *mail)
{
    if(!root)
    {
        //std::cout << "addmail no root return for BST_Postoffice" << std::endl;
        root = new BST_PostOffice_Node(mail);
        return;
    }
    if(mail->getDistrict() == root->district)
    {
       //std::cout << "addmail same district for BST_Postoffice" << std::endl;
        root->addMail(mail);
    }
    if(mail->getDistrict() < root->district) // go left
    {
        if(root->left)
        {
            root->left->addMail(mail);
        }
        else
        {
            root->left = new BST_PostOffice();
            root->left->addMail(mail);
        }
    }
    if(mail->getDistrict() > root->district)
    {
        if(root->right)
        {
            root->right->addMail(mail);            
        }
        else
        {
            root->right = new BST_PostOffice();
            root->right->addMail(mail);
        }
    }
}

void BST_PostOffice_Node::addMail(Mail *mail)
{
    //std::cout << "addmail BST_Node" << std::endl;   
    mailman[mail->getAddressHash()].addMail(mail);
}

// TODO: Given a district, print all of the data in it.
// TIP: Print style depends on type.
void BST_PostOffice::printDistrict(District dist, printType type) const // do not mofidy inonrder
{
    if(!root)
    {
        //std::cout << "printDistrict(dist, tyoe): " << std::endl;
        return;
    }
    else{
        if(root->district == dist)
        {
            std::cout << "The District Mail Report for district " << dist << std::endl;
            root->print(type);
        }
    
        if(dist < root->district)
        {
            if(root->left)
            {
                root->left->printDistrict(dist,type);
            }
            else
            {
                return;
            }
        }
        else
        {
            if(root->right)
            {
                root->right->printDistrict(dist,type);
            }
            else{
                return;
            }
        }
    }

}   

void BST_PostOffice_Node::print(printType type) const // do not modify this 
{
   // std::cout << "The District Mail Report for district " << district << std::endl;
    if(type == inorder)
    {
        /*for(int i = 0; i < HASH_MODULO; i++)
        {
            std::cout << "For Mailman " << i << std::endl; 
            mailman[i].printInOrder();

        }*/
        for(int i = 0; i < HASH_MODULO; i++)
        {
            std::cout << "For Mailman " << i << std::endl; 
            mailman[i].printInOrder();
        }

    }
    else if(type == preorder)
    {
        for(int i = 0; i < HASH_MODULO; i++)
        {
            std::cout << "For Mailman " << i << std::endl; 
            mailman[i].printPreOrder();
        }
    }
    else if(type == postorder)
    {
        for(int i = 0; i < HASH_MODULO; i++)
        {
            std::cout << "For Mailman " << i << std::endl; 
            mailman[i].printPostOrder();
        }
    }
}

// TODO: Given a district and ID of the mailman, print all mail in it
// TIP: Print style depends on type - see the header file
void BST_PostOffice::printMailman(District district, int i, printType type) const
{
    if(!root)
    {
        return;
    }
    if(type == inorder)
    {
        if(root)
        {
            if(root->left)
            {
                root->left->printMailman(district, i, type);
            }
            root->printMailman(i, type);
            if(root->right)
            {
                root->right->printMailman(district, i, type);
            }
        }

    }
    else if(type == preorder)
    {
        if(root)
        {
            root->printMailman(i, type);
            if(root->left)
            {
                root->left->printMailman(district, i, type);
            }
            if(root->right)
            {
                root->right->printMailman(district, i, type);
            }

        }

    }
    else if(type == postorder)
    {
        if(root)
        {
            if(root->left)
            {
                root->left->printMailman(district, i, type);
            }
            if(root->right)
            {
                root->right->printMailman(district, i, type);
            }
            root->printMailman(i, type);
        }
    }
}

void BST_PostOffice_Node::printMailman(int i, printType type) const // i refers to id 
{
    if(type == inorder)
    {
        mailman[i].printInOrder();
    }
    else if(type == preorder)
    {
        mailman[i].printPreOrder();
    }
    else if(type == postorder)
    {
        mailman[i].printPostOrder();
    }
}

// TODO: Other print functions.
void BST_PostOffice::printInOrder() const // correct never fix this 
{

    if(!root)
    {
        return;
    }
    if(root)
    {
        std::cout << "BST Node for District: " << root->district << std::endl;
        if(root->left)
        {
            root->left->printInOrder();
        }

        for(int i = 0; i < HASH_MODULO; i++)
        {
            root->mailman[i].printInOrder();
        }
        if(root->right)
        {
            root->right->printInOrder();
        }
    }
}

void BST_PostOffice::printPostOrder() const
{
    if(!root)
    {
        return;
    }
    if(root)
    {
        std::cout << "BST Node for District: " << root->district << std::endl;
        if(root->left)
        {
            root->left->printPostOrder();
        }
        if(root->right)
        {
            root->right->printPostOrder();
        }
        //std::cout << "BST Node for District: " << root->district << std::endl;
        for(int i = 0; i < HASH_MODULO; i++)
        {
            root->mailman[i].printPostOrder();
        }
    }
}

void BST_PostOffice::printPreOrder() const
{
    if(!root)
    {
        return;
    }
    if(root)
    {
        std::cout << "BST Node for District: " << root->district << std::endl;
        for(int i = 0; i < HASH_MODULO; i++)
        {
            root->mailman[i].printPreOrder();
        }
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
