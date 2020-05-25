#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"intal.h"

static int max(int a,int b) {
    if(a > b)
        return a;
    return b;
}

static int min(int a,int b) {
    if(a < b)
        return a;
    return b;
}

//removes leading zeros
static char* removeZeros(const char* s) {
    int i=0,l = 0;
    //l->length of zeros

    while(s[i] == '0') {
        l++;
        i++;
    }

    if (l == strlen(s)) --l;
    char* res = (char*)malloc((strlen(s) - l + 1)*sizeof(char));
	    
	for(i=0;i<strlen(s)-l;i++) 
        res[i] = s[i+l];   

    res[i] = '\0';
	
	//added now	
	return res;
	
}


char* intal_add(const char* intal1, const char* intal2) {
  
  	int digit;
  	int carry = 0;
  	int maxlength = max(strlen(intal1), strlen(intal2));
  
  	char *temp = (char*)malloc((maxlength+2) * sizeof(char));
  	temp[maxlength+1] = '\0';
  
  	int index = maxlength;
  	int i, j;
  	int length1 = strlen(intal1);
  	int length2 = strlen(intal2);
  
  	int cnt = 0;
  	for(i = length1-1,j = length2-1; (i!=-1 && j!=-1); i--,j--)
  	{
      	int num = (intal1[i] - '0')+ (intal2[j] - '0') + carry;
      	digit = num % 10;
      	carry = num / 10;
      	temp[index] = digit + '0';
      	index--;
      	++cnt;
  	}

  	while(i != -1)
  	{
    	int num = (intal1[i] - '0') + carry;
    	digit = num % 10;
    	carry = num / 10;
    	temp[index] = digit + '0';
    	i--;
    	index--;
    	++cnt;
  	}
  
	while(j != -1)
    {
    	int num = (intal2[j] - '0') + carry;
    	digit = num % 10;
    	carry = num / 10;
    	temp[index] = digit + '0';
    	++cnt;
    	j--;
    	index--;
  	}
  
  	if(carry != 0){
    	temp[index] = (carry) + '0';
    	++cnt;
  	}
  	else{
   		for(int i = 0; i<maxlength+1; i++)
   		{
     		temp[i] = temp[i+index+1];
   		}
   		cnt -= (index);
   		
  	}

  	temp[cnt] = '\0';

	return temp;

}

int intal_compare(const char* intal1, const char* intal2) {
    
  int length1 = strlen(intal1);
  int length2 = strlen(intal2);
  
  if(length1 == length2)
  {
      int i = 0;
      while((intal1[i] == intal2[i]) && intal1[i] != '\0') {
        i++;
      }
      if(i == length1)
          return 0;
      
      if(intal1[i] > intal2[i])
          return 1;
      
      else 
          return -1;
  }
  int maximum = max(length1, length2);
  
  if(maximum == length1)
      return 1;
  
  if(maximum == length2)
      return -1;

  return 0;
}

char* intal_diff(const char* a, const char* b) {

    if(intal_compare(a,b) == -1) {
        return intal_diff(b,a);
    }
        
    char* m = (char*)malloc(sizeof(char)*(strlen(a) + 1));
    strcpy(m,a);
    
    char* n = (char*)malloc(sizeof(char)*(strlen(b) + 1));
    strcpy(n,b);
        
    char* temp = (char*)malloc(sizeof(char)*(strlen(m) + 1));
    temp[strlen(m)] = '\0';
    
    
    int i,diff,j = strlen(m)-1,br = 0;
    for(i=0;i<strlen(m);i++) {
        temp[i] = '0';
    }
    
    for(i=strlen(n)-1;i>=0;i--) {
        br= 0;
        diff = (int)(m[j] - n[i]);

        if(diff < 0) {
           m[j-1] = (m[j-1] - 1) ;
           diff=diff+10;
           br = 1;
        }

        temp[j] = diff + '0';
        j--;

    }

    for(i=j;i>=0;i--) {
            temp[i] = m[i];
    }

	//added now
	free(m);
	free(n);

	char *x = temp;
	temp = removeZeros(temp);
	free(x);

    return temp;
	
}


int intal_search(char **arr, int n, const char* key) {
    int i,pos = -1;

    for(i=0;i<n;i++) {
        if(intal_compare(arr[i],key) == 0) {
            pos = i;
            break;
        }

    }

    return pos;
}

int intal_min(char **arr, int n) {
    int i,pos = 0;

    char* min = arr[0];

    for(i=0;i<n;i++) {
        if(intal_compare(arr[i],min)==-1) {
            min = arr[i];
            pos = i;
        }
    }

    return pos;

}

int intal_max(char** arr, int n) {
    int i,pos = 0;

    char* max = arr[0];

    for(i=0;i<n;i++) {
        if(intal_compare(arr[i],max) == 1) {
            max = arr[i];
            pos = i;
        }
    }
    
    return pos;
}

static void merge(char** arr, int l, int m, int r) {
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    char** L = (char**)malloc(sizeof(char*)*n1);
    char** R = (char**)malloc(sizeof(char*)*n2);

    for(i=0;i<n1;i++) {
        L[i] = (char*)malloc(sizeof(char)*1001);
        strcpy(L[i],arr[l+i]);
    }
    
    for(j=0;j<n2;j++) {
        R[j] = (char*)malloc(sizeof(char)*1001);
        strcpy(R[j],arr[1+m+j]);
    }

    i = 0; 
    j = 0; 
    k = l; 

    while (i < n1 && j < n2)
    {
        if(intal_compare(R[j],L[i]) >= 0)
        {
            strcpy(arr[k],L[i]);
            i++;
        }
        else
        {
            strcpy(arr[k],R[j]);
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        strcpy(arr[k],L[i]);
        i++;
        k++;
    }

    while (j < n2)
    {
        strcpy(arr[k],R[j]);
        j++;
        k++;
    }

    //added now
	for(i=0;i<n1;i++) {
		free(L[i]);    
	}

	for(j=0;j<n2;j++) {
        free(R[j]);
    }

    free(L);
    free(R);

}

static void mergeSort(char** arr, int l, int r) {
    if (l < r) 
    { 
        int m = l+(r-l)/2; 
  
        mergeSort(arr, l, m); 
        mergeSort(arr, m+1, r); 
  
        merge(arr, l, m, r); 
    } 

}

void intal_sort(char** arr, int n) {
        
    mergeSort(arr,0,n-1);
}


int intal_binsearch(char** arr,int n, const char* key) {
    int low = 0,high = n-1,mid;

    while(low <= high) {
        mid = low + (int)((high - low)/2);

        if(intal_compare(arr[mid],key) == 0)
        {
            return mid;
        }

        if(intal_compare(arr[mid],key) == -1)
        {
            low = mid + 1;
        }

        if(intal_compare(arr[mid],key) == 1)
        {
            high = mid - 1;
        }

    }

    return mid;

}

//check how much memory to allocate
char* intal_fibonacci(unsigned int n) {
    int i=1;
    char* res = (char*)malloc(sizeof(char)*1001);

    if(n==0)
        return "0";

    if(n==1)
        return "1";

	char*a = (char*)malloc(sizeof(char)*1001);
	a[0] = '0';
	a[1] = '\0';

    char* b = (char*)malloc(sizeof(char)*1001);
	b[0] = '1';
	b[1] = '\0';

    while(i<=n-1) { 
		char* temp = intal_add(a,b);
		char *temp2 = res;
		res = temp;
		free(temp2);				
		strcpy(a,b);
		strcpy(b,res);        

        i++;
    }

	//added now
	free(a);
	free(b);    

	char* x = removeZeros(res);
	char* y = res;
	res = x;
	free(y);
	
    return res;

}

//multiply with 1 single digit
static char *foo(const char *a, const char *b) {
    int len = strlen(a);
    int digit = (int)(b[0] - '0');

    char res[len + 1];

    int carry = 0;
    /* note, > 0, not >= 0 cos we handle the carry of the last digit separately */
    for (int i = len - 1; i > 0; --i) {                         
        int multiplicand = (int)(a[i] - '0');
        int prod = multiplicand * digit;
        prod += carry;
        carry = prod / 10;
        prod %= 10;
        
        res[len - i - 1] = (char)(prod + '0');
    }

    int final_dig = (int)(a[0] - '0'); 
    int prod = final_dig * digit; prod += carry;

    res[len - 1] = (char)((prod % 10) + '0');
    prod /= 10;
    int extra = 0;
    
    if (prod > 0) {
        res[len] = (char)(prod + '0');
        extra = 1;
    }

    char *ans = (char*)malloc(sizeof(char) * (len + extra + 1));
    ans[len + extra] = '\0';
    int j = 0;
    
    for (int i = len + extra - 1; i > -1; --i) {
        ans[j] = res[i];
        ++j;
    }
    
    return ans;
}

char* intal_multiply(const char* a, const char* b) {
    int len1 = strlen(a);
    int len2 = strlen(b);

	char* ans = foo(a,&b[len2-1]);

    int cnt = 1; //cnt -> number of trailing zeros added
    for (int i = len2 - 2; i > -1; --i) {
        char *ret = foo(a, &b[i]);
        int len = strlen(ret);
        char *res = (char*)malloc(sizeof(char) * (len + cnt + 1));
        res[len + cnt] = '\0';

        for (int j = 0; j < len; ++j) 
			res[j] = ret[j];
        for (int j = len; j < (len + cnt); ++j) 
			res[j] = '0';

		
		char* temp = intal_add(ans,res);
		char* temp2 = ans;
		ans = temp;
		free(temp2);		
	
		free(res);
		free(ret);
        
		++cnt;
    }

	//added now    
	char* temp = removeZeros(ans);
	char* temp2 = ans;
	ans = temp;
	free(temp2);	
    
	return ans;

}

//converts int to char*
static char* int_convert(unsigned int n) {
    
    int r,i = 0,c = 0;
    unsigned int q = n;

    //counting no. of digits
    while(q != 0) {
        c++;
        q/=10;
    }

    char* res = (char*)malloc(sizeof(char)*(c+1));
    i = c-1;

    while(n!=0) {
        r = n%10;
        res[i] = (char)(r + 48);
        i--;
        n/=10;
    }

    res[c] = '\0';
    return res;
}

char* intal_factorial(unsigned int n) {
    if(n==1 || n==0) {
		char *ret = (char*)malloc(sizeof(char) * 2);
		ret[0] = '1'; ret[1] = '\0';
        return ret;
	}

    char* res = int_convert(n);
	//added now
	char* f = intal_factorial(n - 1);

	char* temp = intal_multiply(res, f);
	free(f);
	free(res);
	res = temp;

    return res;
}

char* intal_pow(const char* intal1, unsigned int n) {
        
    unsigned int i;
    char* pro = (char*)malloc(sizeof(char)*1500);
    char* res = (char*)malloc(sizeof(char)*(strlen(intal1)+1));
    strcpy(res,intal1); 

    if(n==0)
    {
        strcpy("pro","1");
        return pro;
    }

    if(n==1)
    {
        strcpy(pro,res);
        return pro;
    }

    strcpy(pro,"1");

    for(i=1;i<=n;i++) {
        
		char* temp = intal_multiply(pro,res);
		char* temp2 = pro;
		pro = temp;
		free(temp2);
		       
    }

    //added now
    free(res);

	char* temp = removeZeros(pro);
	char* temp2 = pro;
	pro = temp;
	free(temp2);

    return pro;
}

char* intal_bincoeff(unsigned int n, unsigned int k) {
    
    if(k > n/2)
        k = n-k;
    
    unsigned int i,j;

    char** dp = (char**)malloc(sizeof(char*)*(k+1));

    for(i=0;i<(k+1);i++) {
        dp[i] = (char*)malloc(sizeof(char)*1001);
        strcpy(dp[i],"0");
    }
    strcpy(dp[0],"1");

    for(i=1;i<=n;i++) {
        for(j = min(i,k);j>0;j--) {
			char* x = intal_add(dp[j],dp[j-1]);
			char* y = dp[j];
			dp[j] = x;
			free(y);        
		}
    }

	//added now
	char* x = removeZeros(dp[k]);
	
	for(i=0;i<(k+1);i++) {
        free(dp[i]);
    }    

	free(dp);

    return x;
}

char* coin_row_problem(char **arr, int n) {
    
    int i;
    char **C = (char**)malloc((n+1)*sizeof(char*));
    
    for(i=0;i<=n;i++) 
        C[i] = (char*)malloc(sizeof(char)*1001);

    strcpy(C[0],"0");
    
    for(i=0;i<n;i++) {
        strcpy(C[i+1],arr[i]);
    }

    char **F = (char**)malloc((n+1)*sizeof(char*));
    for(i=0;i<=n;i++) {
        F[i] = (char*)malloc(sizeof(char)*1001);
    }

    strcpy(F[0],"0");
    strcpy(F[1],C[1]);

    for(i=2;i<=n;i++) {
		char* a = intal_add(C[i],F[i-2]);

        if(intal_compare(a,F[i-1]) == 1)
            strcpy(F[i],a);
        else
            strcpy(F[i],F[i-1]);
		free(a);
    }

	
	char* temp = removeZeros(F[n]);

	for(i=0;i<=n;i++) { 
        free(C[i]);
		free(F[i]);
	}

	free(C);

	free(F);
	
    return temp;

}


//divides an intal by two
static char* divide_two(const char* intal1) {
    char *res = (char*)malloc(sizeof(char)*(strlen(intal1) + 1));
    res[strlen(intal1)] = '\0';
    
    int i,n = strlen(intal1),div = 0,q = 0,rem = 0;
    char x; //char to be copied into res

    if(n==1 && intal1[0] == '0')
        return "0";

    for(i=0;i<n;i++) {
        div = (int)intal1[i] - (int)'0';
        if(rem==1)
            div+=10;
        
        q = div/2;
        rem=div%2;

        x = (char)(q+'0');
        res[i] = x;
    }

	char* temp = removeZeros(res);
	free(res);
	res = temp;
    return res;
}


char* intal_mod(const char* intal1, const char* intal2) { 
    if(intal_compare(intal1,intal2) == -1) {
        char* res = (char*)malloc(sizeof(char)*(strlen(intal1)+1));
        strcpy(res,intal1);
        return res;
   }

    if(intal_compare(intal1,intal2) == 0) {
        char* res = (char*)malloc(sizeof(char)*2);
		res[0] = '0';
		res[1] = '\0';        
		return res;
    }

    char* left = (char*)malloc(sizeof(char)*strlen(intal1)*2);
    char* right = (char*)malloc(sizeof(char)*strlen(intal1)*2);
    char* mid = (char*)malloc(sizeof(char)*strlen(intal1)*2);
    char* ans = (char*)malloc(sizeof(char)*strlen(intal1)*2);
    char* prod = (char*)malloc(sizeof(char)*(strlen(intal1) + strlen(intal2) + 1));
    
    strcpy(left,"0");
    strcpy(right,intal1);

    while(intal_compare(left,right) <= 0) {
        		
		char* temp = intal_add(left,right);
		char* temp2 = mid;
		mid = temp;
		free(temp2);
		
		temp = divide_two(mid);
		temp2 = mid;
		mid = temp;
		free(temp2);

		temp = intal_multiply(mid,intal2);        
		free(prod);
		prod = temp;		

        if(intal_compare(prod,intal1) <= 0) {
            strcpy(ans,mid);         
			temp = intal_add(mid,"1");
			free(left);
			left = temp;

        }
        else {
			temp = intal_diff(mid,"1");
			free(right);
			right = temp;            
        }

		temp = removeZeros(left);
		free(left);
		left = temp;

		temp2 = removeZeros(right);
		free(right);
		right = temp2;

   }

    char* x = intal_multiply(ans,intal2);
    
    char* y = intal_diff(intal1,x);
	char *tmp = y;
	y = removeZeros(y);
	free(tmp);
		
	char* temp = removeZeros(y);
	free(y);
	y = temp;

	free(left);
	free(right);
	free(prod);
	free(ans);
	free(mid);
	free(x);

    return y;

}


char* intal_gcd(const char* intal1, const char* intal2) {

    
    if(intal_compare(intal1,"0")==0)
    {
        char* res = (char*)malloc(sizeof(char)*(strlen(intal2)+1));
        strcpy(res,intal2);
        return res;
    }

    char* i = intal_mod(intal2,intal1);
	char *ret = intal_gcd(i, intal1);
	free(i);
    return ret;
}



