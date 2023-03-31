#include<iostream>
#include<string>
#include<cmath>

using namespace std;

/// Declearing a string to take the plain text
string plain_text;

/// Declearing a string to take the 16 rounds key

string round_keys[16];

/// Declearing a function to convert a number decimal to binary

string dec_to_bin(int dec)
{
    string bin;
    while(dec != 0)
    {
        bin = (dec % 2 == 0 ? "0" : "1") + bin;
        dec = dec / 2;
    }

    while(bin.length() < 4)
    {
        bin = "0" + bin;
    }

    return bin;
}

/// Declearing a function to convert a number Binary to Decimal

int bin_to_dec(string bin)
{
    int dec = 0;
    int counter = 0;
    int size = bin.length();
    for(int i = size - 1; i >= 0; i--)
    {
        if(bin[i] == '1')
        {
            dec += pow(2, counter);
        }
        counter++;

    }
    return dec;
}

/// Create a function to do Lift Shift - 1

string left_shift_one(string key_choose)
{
    string l_s_1 = "";
    for(int i = 1; i < 28; i++)
    {
        l_s_1 += key_choose[i];
    }
    l_s_1 += key_choose[0];
    return l_s_1;
}

/// Create a function to do Left Shift - 2
string left_shift_two(string key_choose)
{
    string l_s_2 = "";
    for (int i = 0; i < 2; i++)
    {
        for(int j = 1; j < 28; j++)
        {
            l_s_2 += key_choose[i];
        }
        l_s_2 += key_choose[0];
        key_choose = l_s_2;
        l_s_2 = "";
    }
    return key_choose;
}

/// Function to compute XOR operation between two strings

string Xor(string a, string b)
{
    string result = "";
    int Size = b.size();
    for(int i = 0; i< Size; i++)
    {
        if(a[i] != b[i])
        {
            result += "1";
        }
        else
        {
            result += "0";
        }
    }
    return result;
}

/// Function to generated the 16 key

void generated_key(string key)
{
    /// Permuted Choose Table - 1
    int pc1[56] = {
            57,49,41,33,25,17,9,
            1,58,50,42,34,26,18,
            10,2,59,51,43,35,27,
            19,11,3,60,52,44,36,
            63,55,47,39,31,23,15,
            7,62,54,46,38,30,22,
            14,6,61,53,45,37,29,
            21,13,5,28,20,12,4 };

    /// Permuted Choose Table - 2

    int pc2[48] = {
            14,17,11,24,1,5,
            3,28,15,6,21,10,
            23,19,12,4,26,8,
            16,7,27,20,13,2,
            41,52,31,37,47,55,
            30,40,51,45,33,48,
            44,49,39,56,34,53,
            46,42,50,36,29,32 };


    /// Compressing the key by passing 56 bit PC1

    string primary_key = "";
    for(int i = 0; i< 56; i++)
    {
        primary_key += key[pc1[i] - 1];
    }

    /// Dividing the key into two subsets(28 bits)

    string left = primary_key.substr(0, 28);
    string right = primary_key.substr(28,28);

    /// Generating the 16 rounds key
    for(int i = 0; i < 16; i++)
    {
        if( i == 0 || i == 1 || i == 8 || i == 15)
        {
            left = left_shift_one(left);
            right = left_shift_one(right);
        }
        else
        {
            left = left_shift_two(left);
            right = left_shift_two(right);
        }

        /// Combine the two string
        string combine_key =  left + right;
        string round_key = "";

        /// Now we pass the combine_key value to the  Permuted Table - 2
        for(int i =0; i < 48; i++)
        {
            round_key += combine_key[pc2[i] - 1];
        }
        round_keys[i] = round_key;
        cout<< "Key "<< i+1<< ": "<<round_keys[i]<<endl;
    }

}


/// Implementation of DES algorithm

string DES()
{
    ///Initial Permutation Table
    int initital_permutation[64] =
    {
        58,50,42,34,26,18,10,2,
        60,52,44,36,28,20,12,4,
        62,54,46,38,30,22,14,6,
        64,56,48,40,32,24,16,8,
        57,49,41,33,25,17,9,1,
        59,51,43,35,27,19,11,3,
        61,53,45,37,29,21,13,5,
        63,55,47,39,31,23,15,7
    };

    /// The Expension Table
    int expention_table[48] =
    {
        32,1,2,3,4,5,4,5,
        6,7,8,9,8,9,10,11,
        12,13,12,13,14,15,16,17,
        16,17,18,19,20,21,20,21,
        22,23,24,25,24,25,26,27,
        28,29,28,29,30,31,32,1
    };

    /// The implementation of S_Box
    /// Here the there 8 s_box

    int s_box[8][4][16] =
    {
        {
            14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
            0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
            4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
            15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13
        },
        {
            15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
            3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
            0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
            13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9
        },
        {
            10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
            13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
            13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
            1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12
        },
        {
            7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
            13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
            10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
            3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14
        },
        {
            2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
            14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
            4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
            11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3
        },
        {
            12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
            10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
            9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
            4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13
        },
        {
             4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
            13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
            1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
            6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12
        },
        {
            13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
            1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
            7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
            2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11
        }
    };
    /// The Final Permutation table
    int Final_permutation[32] =
    {
        16,7,20,21,29,12,28,17,
        1,15,23,26,5,18,31,10,
        2,8,24,14,32,27,3,9,
        19,13,30,6,22,11,4,25
    };

    /// The inverse permutation
    int inverse_permutation[64] =
    {
        40,8,48,16,56,24,64,32,
        39,7,47,15,55,23,63,31,
        38,6,46,14,54,22,62,30,
        37,5,45,13,53,21,61,29,
        36,4,44,12,52,20,60,28,
        35,3,43,11,51,19,59,27,
        34,2,42,10,50,18,58,26,
        33,1,41,9,49,17,57,25
    };

    /// Now applying the initial permutation
    string permutation = "";
    for(int i = 0; i < 64; i++)
    {
        permutation = permutation + plain_text[initital_permutation[i] - 1];
    }

    /// Divided the string into two subset of 32 bits

    string left =  permutation.substr(0, 32);
    string right = permutation.substr(32,32);

    /// The plain text is encrypted 16 times

    for(int i = 0; i< 16;i++)
    {
        string right_extended = "";
        /// Now the right half of the plain text is expended

        for(int i = 0; i < 48; i++)
        {
            right_extended += right[expention_table[i] - 1];
        }
        /// The result is XOR with a key
        string xored = Xor(round_keys[i], right_extended);
        string res = "";

        /// Now dividing the the result into 8 subsets to pass the 8 substitution box.

        for(int i =0; i < 8; i++)
        {
            string row1 = xored.substr(i*6, 1) + xored.substr(i*6 + 5,1);

      		int row = bin_to_dec(row1);
      		string col1 = xored.substr(i*6 + 1,1) + xored.substr(i*6 + 2,1) + xored.substr(i*6 + 3,1) + xored.substr(i*6 + 4,1);;
			int col = bin_to_dec(col1);
			int val = s_box[i][row][col];
			res += dec_to_bin(val);
        }
        // 3.5. Another permutation is applied
		string perm2 ="";
		for(int i = 0; i < 32; i++){
			perm2 += res[Final_permutation[i]-1];
		}
		// 3.6. The result is xored with the left half
		xored = Xor(perm2, left);
		// 3.7. The left and the right parts of the plain text are swapped
		left = xored;
		if(i < 15){
			string temp = right;
			right = xored;
			left = temp;
		}
    }

    // 4. The halves of the plain text are applied
	string combined_text = left + right;
	string ciphertext ="";
	// The inverse of the initial permuttaion is applied
	for(int i = 0; i < 64; i++){
		ciphertext+= combined_text[inverse_permutation[i]-1];
	}
	//And we finally get the cipher text
	return ciphertext;
}


int main()
{
    string key;
    cout<< "Enter 64-bits key for the round key: ";
    cin>>key;
    cout<< "Enter 64 -bit plain text: ";
    cin>>plain_text;
    generated_key(key);
    cout<< "Plain Text: " << plain_text<<endl;
    string cipher_text = DES();
    cout<< "The Cipher text is: "<< cipher_text<< endl;

}
