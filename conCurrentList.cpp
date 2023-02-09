#include <bits/stdc++.h>
template<typename T>
struct node {
    public:
   std::mutex mtex;
   std::shared_ptr<T> data;
   std::unique_ptr<T> next;
   node(): next() {}
   node(T const & value ): data(std::make_shared<T>(value)) {}
           
    };

template<typename t>
class con_list{
   public:
   con_list() {}
   ~con_list() {
     remove_if([](node<t> const&){return true;});
   }
   node<t> head;

   void push_front(t const &value)
   {
    std::unique_ptr<node<t>> temp(value);
    std::lock_guard<std::mutex> lock1(head.mtex);
    temp->next = std::move(head.next);
    head.next = std::move(temp);
   }
 
 template<typename function>
 void for_each(function f)
 {
    node<t>* curr = &head;
    std::unique_lock<std::mutex> lock1(head.mtex);
    while(node<t>* const nxt = curr->next.get())
    {
     std::unique_lock<std::mutex> lock2(nxt.mtex);
     lock1.unlock();
     f(*nxt->data);
     curr = nxt;
     lock1 = std::move(lock2);

    }
 }

   
};

int main()
{
    node<int> n1;
    return 0;
}
