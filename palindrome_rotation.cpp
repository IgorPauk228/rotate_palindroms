#include <iostream>
#include <string>

struct v2{
    size_t ind;
    size_t len;
    std::string word;
};

void init_top_k(int k, v2* top_k){
    for (int i = 0; i < k; ++i){
        top_k[i].ind = std::string::npos;
        top_k[i].len = 0;
    }
}

bool is_palindrome(std::string str, size_t start, size_t end){
    size_t n = end - start + 1;
    for (size_t i = 0; i < n/2; ++i){
        if (str[i + start] != str[end - i]){
            return false;
        }
    }
    return true;
}

void reverse_str(std::string& str, size_t start, size_t end){
    size_t n = end - start + 1;
    for (size_t i = 0; i < n/2; ++i){
        std::swap(str[i + start], str[end - i]);
    }
}

void shift_down(int k, int i, v2* top_k){
    for (int j = k - 1; j > i; --j){
        top_k[j] = top_k[j - 1];
    }
}

void pl_to_topk(size_t index, size_t length, int k, v2* top_k){
    for (int i = 0; i < k; ++i){
        if (top_k[i].ind == std::string::npos){
            top_k[i].ind = index;
            top_k[i].len = length;
            return;
        }
        if (length > top_k[i].len){
            shift_down(k, i, top_k);
            top_k[i].ind = index;
            top_k[i].len = length;
            return;
        }
    }
}

void top_k_palindromes(std:: string str, std::string delims, int k, v2* top_k){
    if (str.empty()){
        return;
    }

    size_t start = str.find_first_not_of(delims);
    size_t end = 0;
    size_t s_len = str.length();

    while (start != s_len){
        start = str.find_first_not_of(delims, end);
        end = str.find_first_of(delims, start);
        if (end == std::string::npos){
            end = s_len - 1;
            if (is_palindrome(str, start, end - 1)){
                pl_to_topk(start, end - start, k, top_k);
            }
            break;
            
        }
        

        if (is_palindrome(str, start, end - 1)){
            pl_to_topk(start, end - start, k, top_k);
        }
        
    }
}

void top_k_words(std::string str, int k, v2* top_k){
    for (int i = 0; i < k; ++i){
        top_k[i].word = str.substr(top_k[i].ind, top_k[i].len);
    }
}

void v2_swap(v2& a, v2& b, std::string& str){
    if (a.ind == b.ind){
        return;
    }

    size_t start = 0;
    size_t end = 0;
    if (a.ind > b.ind){
        start = b.ind;
        end = a.ind + a.len;
        reverse_str(str, start, end);
        reverse_str(str, start, start + a.len);
        reverse_str(str, end - b.len , end);
        reverse_str(str, start + a.len + 1, end - b.len - 1);
        a.ind = start;
        b.ind = end - b.len;
    }

    else{
        start = a.ind;
        end = b.ind + b.len;
        reverse_str(str, start, end);
        reverse_str(str, start, start + b.len);
        reverse_str(str, end - a.len , end);
        reverse_str(str, start + b.len + 1, end - a.len - 1);
        b.ind = start;
        a.ind = end - a.len;
    }
    
}

void top_k_sort(int k, v2* top_k, std::string& str){
    bool flag = false;
    for (int i = 0; i < k; ++i){
        for (int j = 0; j < k - i - 1; ++j){
            if (top_k[j + 1].word < top_k[j].word){
                v2_swap(top_k[j + 1], top_k[j], str);
            }
            flag = true;
        }
        if (!flag) return;
        flag = false;
    }
}

int main(){
    std::string str("The tactical radar detected a fast racecar while the civic leader used a kayak to cross the river");
    std::string delims(" ;,.");

    int k = 3;
    //Храним палиндром в массиве V2 как пару чисел: его индекс и длину
    v2* top_k = new v2[k];

    top_k_palindromes(str, delims, k, top_k);
    top_k_words(str, k, top_k);
    top_k_sort(k, top_k, str);
    

    for (int i = 0; i < k; ++i){
        std::cout << top_k[i].ind << ' ' << top_k[i].len << '\n';
        std::cout << top_k[i].word << '\n';
    }

    std::cout << str << '\n';

    delete[] top_k;
    return 0;
}
