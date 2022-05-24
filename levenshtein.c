
int main(char str1[], char str2[]) {

    // calculando o tamanho das strings str1 e str2
    int m = 0;
    int n = 0;
    char m_i = str1[m];
    char n_i = str2[n];

    while ( m_i != '\0')  {
        m = str1[m_i];
        m++;
    }

    while (n_i != '\0') {
        n = str2[n_i];
        n_i++;
    }

    
}