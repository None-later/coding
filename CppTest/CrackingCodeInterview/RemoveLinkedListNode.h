struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};    

ListNode *removeElements(ListNode *head, int val) 
{
    if (head == NULL)
        return head;
    ListNode* dummy(0);
    dummy->next = head;
    ListNode* curr = head;
    ListNode* prev = dummy;
    while (curr != NULL)
    {
        if (curr->val == val)
        {
            ListNode* temp = curr;
            curr = curr->next;
            prev->next = curr;
                
            temp->next = NULL;
            delete temp;
        }
        else
        {
            curr = curr->next;
            prev = prev->next;
        }    
    }
    return dummy->next;
}