#ifndef BIGINT_H
#define BIGINT_H

#include <bits/stdc++.h>
using namespace std;


typedef long long int ll;

class BIGINT
{

private:

// helper Functions

    int compare(string a, string b) // return 1  if a is greater and 0 if b is greater
{
    // if both is same
    if (a == b)
        return -1;

    int length_a = a.length();
    int length_b = b.length();

    if (length_a > length_b)
        return 1;

    else if (length_b > length_a)
        return 0;
    else
    {
        // means both has same length
        for (int i = 0; i < length_a; i++)
        {
            if (a[i] > b[i])
                return 1;
            else if (a[i] < b[i])
                return 0;
        }
    }

    return 1;
    }

    string RemoveTrailingZeros(string a)
    {
        int i = a.length() - 1;

        while (a[i] == '0' && i > 0)
        {
            a.pop_back();
            i--;
        }
        return a;
    }

    string MultiplyHelper(string first, string second)
    {
        string temp = "";

        reverse(first.begin(), first.end());
        reverse(second.begin(), second.end());

        ll maxlen = max(first.size(), second.size());

        ll CurrSum = 0;
        ll carry = 0;
        ll i;

        for (i = 0; i < maxlen; i++)
        {
            int first_element = i < first.size() ? first[i] - '0' : 0;
            int second_element = i < second.size() ? second[i] - '0' : 0;

            CurrSum = first_element + second_element + carry;

            ll digit = CurrSum % 10;
            temp.push_back(digit + '0');

            carry = CurrSum / 10;
        }

        while (carry)
        {
            temp.push_back((carry % 10) + '0');
            carry = carry / 10;
        }

        reverse(temp.begin(), temp.end());
        return temp;
    }

    // using dp
    bool Check_IsPalindrome(string &s, ll i, ll j, ll &start, ll &maxlen, vector<vector<ll>> &dp)
    {
        if (i >= j)
            return true;
        if (dp[i][j] != -1)
            return dp[i][j];

        bool flag = false;

        if (s[i] == s[j])
            flag = Check_IsPalindrome(s, i + 1, j - 1, start, maxlen, dp);

        if (flag)
        {
            int currlen = j - i + 1;
            if (currlen > maxlen)
            {
                maxlen = currlen;
                start = i;
            }
        }
        dp[i][j] = flag;
        return dp[i][j];
    }

    string add(string a , string b)
    {
        string temp = "";
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());

        ll maxlen = max(a.size(), b.size());

        ll Carry = 0;
        ll i;

        for (i = 0; i < maxlen; i++)
        {
            int first_element = i < a.size() ? a[i] - '0' : 0;
            int second_element = i < b.size() ? b[i] - '0' : 0;

            ll CurrSum = first_element + second_element + Carry;

            temp.push_back((CurrSum % 10) + '0');

            Carry = CurrSum / 10;
        }

        while (Carry)
        {
            temp.push_back((Carry % 10) + '0');
            Carry = Carry / 10;
        }

        reverse(temp.begin(), temp.end());

        return temp;
    }

    string sub(string a , string second)
    {
        bool which_greater = Compare(second);

        string temp = "";
        string sub1, sub2;

        if (which_greater)
        {
            sub1 = a;
            sub2 = second;
        }
        else
        {
            sub1 = second;
            sub2 = a;
        }

        reverse(sub1.begin(), sub1.end());
        reverse(sub2.begin(), sub2.end());

        int min_len = sub2.length();
        int max_len = sub1.length();

        // add 0 to small string

        for (int i = min_len; i < max_len; i++)
        {
            sub2.push_back(0 + '0');
        }

        // now interate on both string

        for (int i = 0; i < max_len; i++)
        {
            if (sub1[i] < sub2[i])
            {
                int a = sub1[i] - '0';
                a = 10 + a;

                int b = sub2[i] - '0';
                a = a - b;

                temp.push_back(a + '0');
                sub1[i + 1]--; // carry wala seen
            }
            else
            {
                temp.push_back(((sub1[i] - '0') - (sub2[i] - '0')) + '0');
            }
        }

        temp = RemoveTrailingZeros(temp);

        // if second number is greater
        if (!which_greater)
            temp.push_back('-');

        // temp = RemoveTrailingZeros(temp);
        reverse(temp.begin(), temp.end());
        return temp;
    }

    string multiply(string a , string b)
    {
        bool neg = ((a[0] == '-' && b[0] == '-') || (a[0] != '-' && b[0] != '-')) ? 0 : 1;
        string multiplicand, multiplier;
        if (a.size() > b.size())
            multiplicand = a, multiplier = b;
        else
            multiplicand = b, multiplier = a;

        reverse(multiplicand.begin(), multiplicand.end());
        reverse(multiplier.begin(), multiplier.end());

        if (multiplicand[multiplicand.size() - 1] == '-')
            multiplicand.pop_back();
        if (multiplier[multiplier.size() - 1] == '-')
            multiplier.pop_back();

        string ans = "0";

        for (int i = 0; i < multiplier.size(); i++)
        {
            ll carry = 0;
            ll mul = multiplier[i] - '0';
            string temp = "";

            for (int j = 0; j < multiplicand.size(); j++)
            {
                ll cmul = (multiplicand[j] - '0') * mul + carry;
                temp.push_back((cmul % 10) + '0');
                carry = cmul / 10;
            }
            while (carry)
            {
                temp.push_back((carry % 10) + '0');
                carry /= 10;
            }
            reverse(temp.begin(), temp.end());
            ll zeroadd = i;
            while (zeroadd--)
                temp.push_back('0');

            ans = MultiplyHelper(ans, temp);
        }
        reverse(ans.begin(), ans.end());
        ans = RemoveTrailingZeros(ans);
        if (neg)
            ans.push_back('-');
        reverse(ans.begin(), ans.end());
        return ans;
    }

    string divideByTwo(string number)
    {
        string result;
        int carry = 0;
        for (char c : number)
        {
            int current = carry * 10 + (c - '0');
            result.push_back(current / 2 + '0');
            carry = current % 2;
        }
        while (result[0] == '0' && result.size() >= 1)
        {
            result.erase(result.begin());
        }
        return result;
    }

    string divide_Table_Calculator(string a, string b)
    {
        string multiplicand, multiplier;
        if (a.size() > b.size())
            multiplicand = a, multiplier = b;
        else
            multiplicand = b, multiplier = a;

        reverse(multiplicand.begin(), multiplicand.end());
        reverse(multiplier.begin(), multiplier.end());

        string ans = "0";

        for (int i = 0; i < multiplier.size(); i++)
        {
            ll carry = 0;
            ll mul = multiplier[i] - '0';
            string temp = "";

            for (int j = 0; j < multiplicand.size(); j++)
            {
                ll cmul = (multiplicand[j] - '0') * mul + carry;
                temp.push_back((cmul % 10) + '0');
                carry = cmul / 10;
            }
            while (carry)
            {
                temp.push_back((carry % 10) + '0');
                carry /= 10;
            }
            reverse(temp.begin(), temp.end());
            ll zeroadd = i;
            while (zeroadd--)
                temp.push_back('0');

            ans = MultiplyHelper(ans, temp);
        }
        reverse(ans.begin(), ans.end());
        ans = RemoveTrailingZeros(ans);
        reverse(ans.begin(), ans.end());
        return ans;
    }
    
    string divide_intermediate_subtractor(string a, string b)
    {
        string temp = "";
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        for (int i = 0; i < a.size(); i++)
        {
            ll csub = a[i] - '0' - (i < b.size() ? b[i] - '0' : 0);
            if (csub >= 0)
            {
                temp.push_back(csub + '0');
            }
            else
            {
                csub = 10 + (a[i] - '0') - (i < b.size() ? b[i] - '0' : 0);
                a[i + 1] = (a[i + 1] - '0' - 1) + '0';
                temp.push_back(csub + '0');
            }
        }
        temp = RemoveTrailingZeros(temp);
        reverse(temp.begin(), temp.end());
        return temp;
    }

public:

    string a;

    // constructor
    BIGINT()
    {
        a = "";
    }

    // intialization list
    BIGINT(string t) : a(t) {};

    BIGINT(BIGINT &t)
    {

        a = t.a;
    }

    void Print()
    {
        cout << a;
    }



    string Add(string b)
    {
        string temp = "";
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());

        ll maxlen = max(a.size(), b.size());

        ll Carry = 0;
        ll i;

        for (i = 0; i < maxlen; i++)
        {
            int first_element = i < a.size() ? a[i] - '0' : 0;

            int second_element = i < b.size() ? b[i] - '0' : 0;

            ll CurrSum = first_element + second_element + Carry;

            temp.push_back((CurrSum % 10) + '0');

            Carry = CurrSum / 10;

        }

        while (Carry)
        {
            temp.push_back((Carry % 10) + '0');
            Carry = Carry / 10;
        }

        reverse(temp.begin(), temp.end());

        return temp;
    }

    string Abs()
    {
        string temp = a;
        if(temp[0] >=0)
            return a;
        if (temp[0] == '-')
        {
            reverse(temp.begin(), temp.end());
            temp.pop_back();
            reverse(temp.begin(), temp.end());
        }
        return temp;
    }

    int Compare(string b) // return 1 if a is greater , 0 if b is greater , -1 if both same
    {
        int length_a = a.length();
        int length_b = b.length();

        if (length_a > length_b)
        {
            return 1;
        }
        else if (length_b > length_a)
        {
            return 0;
        }
        else
        {
            // for same lenght
            for (int i = 0; i < length_a; i++)
            {
                if (a[i] > b[i])
                    return 1;
                else if (b[i] > a[i])
                    return 0;
            }
        }

        return -1;
    }

    string Sub(string second)
    {
        bool which_greater = Compare(second);

        string temp = "";
        string sub1, sub2;

        if (which_greater)
        {
            sub1 = a;
            sub2 = second;
        }
        else
        {
            sub1 = second;
            sub2 = a;
        }

        reverse(sub1.begin(), sub1.end());
        reverse(sub2.begin(), sub2.end());

        int min_len = sub2.length();
        int max_len = sub1.length();

        // add 0 to small string

        for (int i = min_len; i < max_len; i++)
        {
            sub2.push_back(0 + '0');
        }

        // now interate on both string

        for (int i = 0; i < max_len; i++)
        {
            if (sub1[i] < sub2[i])
            {
                int a = sub1[i] - '0';
                a = 10 + a;

                int b = sub2[i] - '0';
                a = a - b;

                temp.push_back(a + '0');
                sub1[i + 1]--; // carry wala seen
            }
            else
            {
                temp.push_back(((sub1[i] - '0') - (sub2[i] - '0')) + '0');
            }
        }

        temp = RemoveTrailingZeros(temp);

        // if second number is greater
        if (!which_greater)
            temp.push_back('-');

        // temp = RemoveTrailingZeros(temp);
        reverse(temp.begin(), temp.end());
        return temp;
    }

    string Multiply(string b)
    {
        bool neg = ((a[0] == '-' && b[0] == '-') || (a[0] != '-' && b[0] != '-')) ? 0 : 1;
        string multiplicand, multiplier;
        if (a.size() > b.size())
            multiplicand = a, multiplier = b;
        else
            multiplicand = b, multiplier = a;

        reverse(multiplicand.begin(), multiplicand.end());
        reverse(multiplier.begin(), multiplier.end());

        if (multiplicand[multiplicand.size() - 1] == '-')
            multiplicand.pop_back();
        if (multiplier[multiplier.size() - 1] == '-')
            multiplier.pop_back();

        string ans = "0";

        for (int i = 0; i < multiplier.size(); i++)
        {
            ll carry = 0;
            ll mul = multiplier[i] - '0';
            string temp = "";

            for (int j = 0; j < multiplicand.size(); j++)
            {
                ll cmul = (multiplicand[j] - '0') * mul + carry;
                temp.push_back((cmul % 10) + '0');
                carry = cmul / 10;
            }
            while (carry)
            {
                temp.push_back((carry % 10) + '0');
                carry /= 10;
            }
            reverse(temp.begin(), temp.end());
            ll zeroadd = i;
            while (zeroadd--)
                temp.push_back('0');

            ans = MultiplyHelper(ans, temp);
        }
        reverse(ans.begin(), ans.end());
        ans = RemoveTrailingZeros(ans);
        if (neg)
            ans.push_back('-');
        reverse(ans.begin(), ans.end());
        return ans;
    }

    string Divide(string b)
    {
        if(a[0] == '-' || b[0] == '-')
            return "ERROR -> Your String Contains , negative number ";

        int found = a.find(' ');
        int found2 = b.find(' ');

        if(found != string::npos)
            return "ERROR , Your String Contains Space in it .";
        if(found2 != string::npos)
            return "ERROR , Your String Contains Space in it .";
    

        if (b == "1")
            return a;
        if (a == "0" || a == "00")
            return "0";
        if (b == "0" || b == "00")
            return "DIVIDE OVERFLOW";
        int cmp = compare(a, b);
        if (cmp == -1) // a & b equal
            return "1";
        else if (cmp == 0) // b > a
            return "0";
        else
        {
            vector<string> table;
            table.clear();
            table.push_back("-1");
            for (int i = 1; i <= 9; i++)
                table.push_back(divide_Table_Calculator(b, to_string(i)));


            string q, r, temp;
            int i = 0;

            while (1)
            {
                bool t = 0;
                if (compare(temp, b) == 0 && i < a.size())
                {
                    t = 1;

                    temp.push_back(a[i]);

                    i++;
                    if (compare(temp, b) == 0)
                        q.push_back('0');
                }
                else
                {
                    bool inloop = 0;
                    reverse(temp.begin(), temp.end());
                    temp = RemoveTrailingZeros(temp);
                    reverse(temp.begin(), temp.end());

                    int j = table.size() - 1;

                    while (compare(temp, table[j]) == 0 && temp != "0" && j >= 1)
                    {
                        inloop = 1, --j;
                    }

                    // temp = dis(temp, table[j]);
                    
                    temp = sub(temp,table[j]);

                    if (temp.size() == 1 && temp[0] == '0')
                        temp.clear();
                    
                    q.push_back( j + '0');
                    // if (inloop && j != 0){
                        
                    //     q.push_back(j + '0');
                    //     cout<<"q is : "<<q<<endl;
                    // }
                        
                    // else
                    // {
                    //     q.push_back('0');
                    //     cout<<"else q is : "<<q<<endl;
                    // }

                    t = 0;
                }
                if (compare(temp, b) == 0 && i == a.size())
                {
                    break;
                }
            }
            reverse(q.begin(), q.end());
            q = RemoveTrailingZeros(q);
            reverse(q.begin(), q.end());
            return q;
        }
    }

    inline string ValueOf(string temp)
    {
        a = temp;  return a;  
    }

    bool IsPalindrome()
    {
        
        if( (a[0] == '0') || ( a[0] == '-'))
        {
            cout<<"Invalid String , The string contains negative number or only 0 in it ."<<endl;
            return false;
        }

        ll start = 0;
        ll end = a.length()-1;

        while( start <= end)
        {

            if(a[start] != a[end])
                return false;
            else
            {
                start++;
                end--;
            }
        }

        return true;
    }

    string Longest_palindromic()
    {
        ll start = 0;
        ll maxlen = 1;
        ll length = a.size();

        vector<vector<ll>> dp(a.size(), vector<ll>(a.size(), -1));

        for (ll i = 0; i < length ; i++)
        {
            for (ll j = i; j < length ; j++)
            {
                bool t = Check_IsPalindrome(a, i, j, start, maxlen, dp);
            }
        }

        return a.substr(start, maxlen);
    }

    string SquareRoot()
    {
        if(a == "0" || a == "1")
            return a;

        string start = "0";
        string end = a;
        string ans;

        while( (compare(start,end) == -1) || compare(start,end) != 1)
        {
            string mid = divideByTwo(add(start, end));

            string midSquared = multiply(mid,mid);

            int comp = compare(midSquared , a);

            if(comp == -1)
            {
                return mid;
            }
            else if(comp == 1)
            {
                end = sub(mid,"1");
            }
            else
            {
                ans = mid;
                start = add(mid,"1");
            }
        }

        return ans;
    }

    string Factorial()
    {

        ll num = stoi(a);
        string ans = "1";
        try{
            if(num < 1)
                throw num;

            for(ll i=1 ; i <= num ; i++)
            {
                ans = multiply(ans,to_string(i));
            }
        }
        catch(ll num)
        {
            cout<<"ERROR , The Number is Less than or Equals to 0 : " << num<<endl;
            return "";
        }

        return ans;
    }

    string reverse_BIGINT()
    {
        if (a.size() == 0 || a.size() == 1)
            return a;



        ll size = a.size()-1;
        
        if(a[0] == '-')
        {
            ll i = 1;
            while (i < size)
            {
                swap(a[i++], a[size--]);
            }
        }
        else
        {
            ll i = 0;
            while (i < size)
            {
                swap(a[i++], a[size--]);
            }
        }


        return a;   
    }

    

};

#endif

