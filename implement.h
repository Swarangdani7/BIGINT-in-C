#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

static char* InitializeBigint(){
    // initializes an empty char array of 1000 digits
    char* bigptr = (char*)malloc(1001*sizeof(bigptr));

    for(int i=0; i<1000; ++i){
        bigptr[i] = '0';
    }

    bigptr[1000] = '\0';

    return bigptr;
}

static bool empty(const char* ptr){
    // returns true if char array is empty otherwise returns false
    if(strlen(ptr) == 0){
        return true;
    }
    return false;
}

static int find_max(int num1, int num2){
    // finds the greater number between num1 and num2;
    if(num1 > num2){
        return num1;
    }
    else{
        return num2;
    }
}

static int find_min(int num1, int num2){
    // finds the smaller number between num1 and num2
    if(num1 < num1){
        return num1;
    }
    else{
        return num2;
    }
}

static int CountLeadingZeros(const char* ptr){
    // Counts and returns number of leading zeros "00123" -> 2
    int i = 0;
    for(i=0; i<strlen(ptr); ++i){
        if(ptr[i] != 48){
            break;
        }
    }
    return i;
}

static int length(const char* ptr){
    // returns the length of bigint
    int lz = CountLeadingZeros(ptr);
    return strlen(ptr)-lz;
}

static char* RemoveLeadingZeros(char* ptr){
    // removes leading zeros and returns a new char array "00123" -> "123"
    // NOTE: Char array is passed by reference, by calling this function your orginal array will be affected 
    int len = strlen(ptr);
    int z = CountLeadingZeros(ptr);
    int ch=0;
    
    if(z == 0){
        return ptr;
    }
    else{
        int id = 0;
        for(int i=z; i<len; ++i){
            ptr[id] = ptr[i];
            id++; 
        }
        if(id == 0){
            ptr[0] = 48;
            ptr[1] = '\0';
        }
        else{
            ptr[id] = '\0';
        }
        return ptr;
    }
}

static void HelperDiffer(const char* arr1, const char* arr2, char* res){
    // A helper function for performing subtraction
    // Returns the difference of two Bigints
    int z1 = CountLeadingZeros(arr1);
    int z2 = CountLeadingZeros(arr2);
    
    int len1 = length(arr1)-1; 
    int len2 = length(arr2)-1;
    int id = len1,carry=0,st=999;

    while(id >= 0){
        if(len2 < 0){
            if(arr1[z1+len1]-carry >= 48){
                res[st] = arr1[z1+len1]-carry;
                carry = 0;
            }
            else{
                int c = 10+arr1[z1+len1];
                int val = c - 48 - carry;
                res[st] = 48+val;
                carry = 1;
            }
            len1--;
        }
        else if(arr1[z1+len1]-carry >= arr2[z2+len2]){
            int val = arr1[z1+len1]-arr2[z2+len2]-carry;
            res[st] = 48+val;
            carry = 0;
            len1--;
            len2--;
        }
        else{
            int c = 10+arr1[z1+len1];
            int val = c - arr2[z2+len2]-carry;
            res[st] = 48+val;
            carry=1;
            len1--;
            len2--;
        }
        id--;
        st--;
    }
}

static void HelperMultiplier(const char* arr1, const char* arr2, char* res){
    // A helper function for performing multiplication
    int powerfactor = 0;

    for(int i=strlen(arr2)-1; i>=CountLeadingZeros(arr2); --i){
        int carry = 0;
        int st = 999;
        for(int j=strlen(arr1)-1; j>=CountLeadingZeros(arr1); --j){
            int prod = (arr2[i]-48) * (arr1[j]-48) + carry + res[st-powerfactor]-48;
            res[st-powerfactor] = 48+prod%10;
            carry = prod/10;
            st--;
        }
        if(carry > 0){
            res[st-powerfactor] = 48+carry;
        }
        powerfactor++;
    }
}

int CompareBigint(const char* big1, const char* big2){
    int cnt1 = CountLeadingZeros(big1);
    int cnt2 = CountLeadingZeros(big2);
    int len1 = length(big1);
    int len2 = length(big2);

    if(len1 > len2){
        return 1;
    }
    else if(len1 < len2){
        return -1;
    }
    else{
        int val=0;
        int id = 0;
        while(id < len1){
            if(big1[id+cnt1] > big2[id+cnt2]){
                val = 1;
                break;
            }
            else if(big1[id+cnt1] < big2[id+cnt2]){
                val = -1;
                break;
            }
            id++;
        }
        return val;
    }
}

char* BigintAdder(const char* ptr1,const char* ptr2){
    char* ans = InitializeBigint(); 
    int Max, carry=0, st=999;
    int ptr1_zer = CountLeadingZeros(ptr1);
    int ptr2_zer = CountLeadingZeros(ptr2);
    int ptr1_len = length(ptr1)-1;
    int ptr2_len = length(ptr2)-1;
    
    Max = find_max(ptr1_len, ptr2_len);

    while(Max >= 0){
        if(ptr1_len >= 0 && ptr2_len >= 0){
            int val = ptr1[ptr1_zer+ptr1_len]+ptr2[ptr2_zer+ptr2_len]+carry-96;
            ans[st] = 48+val%10;
            carry = val/10;
            ptr1_len--;
            ptr2_len--;
            st--;
        }
        else if(ptr2_len < 0){
            int val = ptr1[ptr1_zer+ptr1_len]+carry-48;
            ans[st] = 48+val%10;
            carry = val/10;
            ptr1_len--;
            st--;
        }
        else{
            int val = ptr2[ptr2_zer+ptr2_len]+carry-48;
            ans[st] = 48+val%10;
            carry = val/10;
            ptr2_len--;
            st--;
        }
        Max--;
    }
    ans[st] = 48+carry;
    RemoveLeadingZeros(ans);
    return ans;
}

char* BigintDiffer(const char* ptr1, const char* ptr2){
    int ptr1_len = length(ptr1);
    int ptr2_len = length(ptr2); 
    int comp = CompareBigint(ptr1,ptr2);
    char* ans = InitializeBigint();
    if(ptr1_len >= ptr2_len && (comp == 1 || comp == 0)){
        HelperDiffer(ptr1,ptr2,ans);
    }
    else{
        HelperDiffer(ptr2,ptr1,ans);
    }
    RemoveLeadingZeros(ans);
    return ans;
}

char* BigintMultiplier(const char* ptr1,const char* ptr2){
    char* ans = InitializeBigint();
    int ptr1_len = length(ptr1);
    int ptr2_len = length(ptr2);
    int z1 = CountLeadingZeros(ptr1);
    int z2 = CountLeadingZeros(ptr2);
    int st = 999;

    if(ptr1_len == 0 || ptr2_len == 0){
        RemoveLeadingZeros(ans);
        return ans;
    }

    if(ptr1_len == 1){
        if(ptr1[z1+ptr1_len-1] == 49){
            for(int i=strlen(ptr2); i>=z2; --i){
                ans[st] = ptr2[i];
                st--;
            }
            RemoveLeadingZeros(ans);
            return ans;
        }
    }
    if(ptr2_len == 1){
        if(ptr2[z2+ptr2_len-1] == 49){
            for(int i=strlen(ptr1)-1; i>=z1; --i){
                ans[st] = ptr1[i];
                st--;
            }
            RemoveLeadingZeros(ans);
            return ans;
        }
    }
    
    if(ptr1_len >= ptr2_len){
        HelperMultiplier(ptr1,ptr2,ans);
        RemoveLeadingZeros(ans);
    }
    else{
        HelperMultiplier(ptr2,ptr1,ans);
        RemoveLeadingZeros(ans);
    }
    return ans;
}

char* BigintFactorial(unsigned int n){
    char* ans = InitializeBigint();
    if(n == 0){
        RemoveLeadingZeros(ans);
        return ans; 
    }
    if(n == 1){
        ans[999] = '1';
        RemoveLeadingZeros(ans);
        return ans;
    }
    ans[999] = '1';
    char* bigint_num = InitializeBigint();
    bigint_num[999] = '1';
    for(int i=2; i<=n; ++i){
        bigint_num = BigintAdder(bigint_num,"1");
        ans = BigintMultiplier(bigint_num,ans);
    }
    free(bigint_num);
    return ans;
}

char* BigintFibonacci(unsigned int n){
    char* n0 = InitializeBigint();
    if(n == 0){
        RemoveLeadingZeros(n0);
        return n0;
    }
    char* n1 = InitializeBigint();
    n1[999] = '1';
    if(n == 1){
        free(n0);
        RemoveLeadingZeros(n1);
        return n1;
    }
    char* temp;
    for(int i=2; i<=n; ++i){
        temp = BigintAdder(n0,n1);
        n0 = n1;
        n1 = temp;
    }
    free(n0);
    free(temp);
    return n1;
}