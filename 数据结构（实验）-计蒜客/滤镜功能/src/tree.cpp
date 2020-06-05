#include "tree.h"
#include <queue>

Node::Node() {
    p=NULL;
    children = new Node*[4];
    for(int i=0;i<4;i++)
    {
        *(children+i)=NULL;
    }
    width=0;
    height=0;
    leaf=false;
    x=0;
    y=0;
    mean_b=0;
    mean_g=0;
    mean_r=0;
    cut=0;

}

Node::Node(PNG* corner, int input_width, int input_height, int x, int y) {
    p=corner;
    children = new Node*[4];
    for(int i=0;i<4;i++)
    {
        *(children+i)=NULL;
    }   
    width=input_width;
    height=input_height;
    if(input_width==1 && input_height==1)
        leaf=true;
    else
        leaf=false;
    this->x=x;
    this->y=y;
    mean_r=get_pxl()->red;
    mean_g=get_pxl()->green;
    mean_b=get_pxl()->blue;
    r_r=mean_r;
    r_g=mean_g;
    r_b=mean_b;
    cut=0;

}

Node::Node(Node &other) {
    p=new PNG();
    *p=*(other.p);
    children = new Node*[4];
    for(int i=0;i<4;i++)
    {
        *(children+i)=other.children[i];
    }
    width=other.width;
    height=other.height;
    leaf=other.leaf;
    this->x=other.x;
    this->y=other.y;
    mean_r=other.mean_r;
    mean_g=other.mean_g;
    mean_b=other.mean_b;
    r_r=mean_r;
    r_g=mean_g;
    r_b=mean_b;
    cut=other.cut;

}

Node::Node(Node &&other) {
    p=other.p;
    children=other.children;
    width=other.width;
    height=other.height;
    leaf=other.leaf;
    this->x=other.x;
    this->y=other.y;
    mean_r=other.mean_r;
    mean_g=other.mean_g;
    mean_b=other.mean_b;
    r_r=mean_r;
    r_g=mean_g;
    r_b=mean_b;
    cut=other.cut;
    other.p=nullptr;
    other.children=nullptr;
}

Node& Node::operator=(Node &other) {
    if(this==&other)return *this;
    p=other.p;
    children = new Node*[4];
    for(int i=0;i<4;i++)
    {
        *(children+i)=other.children[i];
    }
    width=other.width;
    height=other.height;
    leaf=other.leaf;
    this->x=other.x;
    this->y=other.y;
    mean_r=other.mean_r;
    mean_g=other.mean_g;
    mean_b=other.mean_b;
    r_r=mean_r;
    r_g=mean_g;
    r_b=mean_b;
    cut=other.cut;
    return *this;
}

Node& Node::operator=(Node &&other) {
    if(this==&other)return *this;
    if(p!=NULL) delete p;
    if(children!=NULL) delete[] p;
    p=other.p;
    children=other.children;
    width=other.width;
    height=other.height;
    leaf=other.leaf;
    this->x=other.x;
    this->y=other.y;
    mean_r=other.mean_r;
    mean_g=other.mean_g;
    mean_b=other.mean_b;
    r_r=mean_r;
    r_g=mean_g;
    r_b=mean_b;
    cut=other.cut;
    other.p=nullptr;
    other.children=nullptr;
    return *this;

}
int Node::get_heigth(){
    return height;
}
int Node::get_width(){
    return width;
}
int Node::get_x(){
    return x;
}
int Node::get_y(){
    return y;
}
bool Node::Orleaf(){
    return leaf;
}
void Node::Set_rgb(int r,int g,int b){
    mean_r=r;
    mean_g=g;
    mean_b=b;
    return;
}

void Tree::judge(int threshold) {
    if(this->root==NULL)return;
    pre_judege(root,threshold);
    restore(root);
    cal_aver(root);

    return;
}
void Tree::pre_judege(Node *node, int threshold){
    int vaild=0;
    if(node->Orleaf())return;
    for(int i=0;i<4;i++){
        if(node->children[i]!=NULL){
            pre_judege(node->children[i],threshold);
            vaild++;
        }
    }
    node->cut=max_cut(node);
    if(node->cut>2)return;

    //
    int sum_r=0,sum_g=0,sum_b=0;
    for(int i=0;i<4;i++){
        if(node->children[i]!=NULL)
        {
            sum_r+=node->children[i]->mean_r;
            sum_g+=node->children[i]->mean_g;
            sum_b+=node->children[i]->mean_b;
        }
    }
    //
    int mean_r=0,mean_g=0,mean_b=0;
    node->mean_r=mean_r=sum_r/vaild;
    node->mean_g=mean_g=sum_g/vaild;
    node->mean_b=mean_b=sum_b/vaild;
    //
    int var_sum=0,var;
    for(int i=0;i<4;i++){
        if(node->children[i]!=NULL){
            Node *child=node->children[i];
            var_sum+=(child->mean_r-mean_r)*(child->mean_r-mean_r)+(child->mean_g-mean_g)*(child->mean_g-mean_g)+(child->mean_b-mean_b)*(child->mean_b-mean_b);
        }
    }
    var=var_sum/(30*vaild);
    if(var<threshold){
        set_mean(node,mean_r,mean_g,mean_b);
    }
        
}
int Tree::set_mean(Node *node, int r, int g, int b){
    if(node==NULL)return -1;
    node->Set_rgb(r,g,b);
    if(node->Orleaf()){
        node->cut++;
        node->get_pxl()->red=node->mean_r;
        node->get_pxl()->green=node->mean_g;
        node->get_pxl()->blue=node->mean_b;
        return 0;
    }
    for(int i=0;i<4;i++){
        if(node->children[i]!=NULL){
            set_mean(node->children[i],r,g,b);
            node->cut=(node->cut)>(node->children[i]->cut)?(node->cut):(node->children[i]->cut);

        }
    }
    return 1;
}
int Tree::Set_all(Node *node){
    if(node==NULL)return -1;
    if(node->Orleaf()){
        node->get_pxl()->red=node->mean_r;
        node->get_pxl()->green=node->mean_g;
        node->get_pxl()->blue=node->mean_b;
        return 0;
    }
    for(int i=0;i<4;i++){
        if(node->children[i]!=NULL){
            Set_all(node->children[i]);
        }
    }
    return 1;
}
int Tree::restore(Node *node){
    if(node==NULL)return -1;
    if(node->Orleaf()){
        node->mean_r=node->r_r;
        node->mean_g=node->r_g;
        node->mean_b=node->r_b;
        return 0;
    }
    for(int i=0;i<4;i++){
        if(node->children[i]!=NULL){
            restore(node->children[i]);
        }
    }
    return 1;
}


int Tree::max_cut(Node *node){
    if(node->Orleaf())return node->cut;
    int ans=0;
    for(int i=0;i<4;i++){
        if(node->children[i]!=NULL){
            ans=ans>max_cut(node->children[i])?ans:max_cut(node->children[i]);
        }
    }
    return ans;
}

void Tree::load_png(PNG *png) {
    Node *tmp=new Node(png,png->get_width(),png->get_height(),0,0);
    root=tmp;
    std::queue<Node*> q;
    q.push(root);
    while(!q.empty())
    {
        Node *b=q.front();
        q.pop();
        int w[4],h[4],x[4],y[4];
        w[0]=w[2]=b->get_width()/2;
        w[1]=w[3]=b->get_width()-w[0];
        h[0]=h[1]=b->get_heigth()/2;
        h[2]=h[3]=b->get_heigth()-h[0];
        x[0]=x[2]=b->get_x();
        x[1]=x[3]=b->get_x()+w[0];
        y[0]=y[1]=b->get_y();
        y[2]=y[3]=b->get_y()+h[0];

        for(int i=0;i<4;i++)
        {
            if(w[i]==1 && h[i]==1)
                b->children[i]=new Node(png,w[i],h[i],x[i],y[i]);
            else if (w[i]==0 || h[i]==0)
                continue;
            else
            {
                b->children[i]=new Node(png,w[i],h[i],x[i],y[i]);
                q.push(b->children[i]);
            }
            
        }
    }
    cal_aver(root);
    


}
void Tree::cal_aver(Node *node){
    if(node->Orleaf())return;
    int vaild=0,sum_r=0,sum_g=0,sum_b=0;
    for(int i=0;i<4;i++)
    {
        if(node->children[i]!=NULL)
        {
            vaild++;
            cal_aver(node->children[i]);
            sum_r+=node->children[i]->mean_r;
            sum_g+=node->children[i]->mean_g;
            sum_b+=node->children[i]->mean_b;
        }
    }
    node->Set_rgb(sum_r/vaild,sum_g/vaild,sum_b/vaild);
}

/*
 ================================================
 ====DO NOT MODIFY ANY OF THE FUNCTIONS BELOW====
 ==============请不要修改以下任何函数================
 ================================================
 */

Node::~Node() {
    for (int i = 0; i < 4; i++) {
        if (children[i]!=NULL) {
            delete children[i];
        }
    }
    delete[] children;
}

void Node::print() {
    if (children[0] != NULL) {
        children[0]->print();
    }
    if (children[1] != NULL) {
        children[1]->print();
    }
    if (children[2] != NULL) {
        children[2]->print();
    }
    if (children[3] != NULL) {
        children[3]->print();
    }
    printf("Red: %u, Green: %u, Blue: %u, Width: %d, Height: %d\n", mean_r, mean_g, mean_b, width, height);
    //printf("Red: %u, Green: %u, Blue: %u, Width: %d, Height: %d,", p->red, p->green, p->blue, width, height);
    std::cout << "Leaf: " << leaf << std::endl;
    return;
}

pxl* Node::get_pxl() {
    return p->get_pxl(x,y);
}

Tree::Tree() {
    root = new Node();
}

Tree::~Tree() {
    delete root;
}

Tree::Tree(Tree &other) {
    if (other.root != NULL) {
        root = new Node(*other.root);
    }
}

Tree& Tree::operator=(Tree &other) {
    if (other.root != NULL && &other != this) {
        root = new Node(*(other.root));
    }
    return *this;
}

pxl *Tree::get_pxl() {
    return root->get_pxl();
}

void Tree::print() {
    root->print();
}
