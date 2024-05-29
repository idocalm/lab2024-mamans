
void read_set(set *s, int *arr) {
    
    free(s -> values);
    s -> values = (int*) malloc(16 * sizeof(int));
    s -> size = 0;


    int i = 0;
    int size = 0;

    while (arr[i] != -1) {

        /* get the current element x */
        int x = arr[i];

        /* check if x is not in the set s */
        if (s -> values[x / 8] & (1 << (x % 8)) == 0) {
            /* increment size */
            s -> values[x / 8] |= 1 << (x % 8);
            size++;
        }

        i++;
    }

    s -> size = size;
}

void print_set(set *s) {

    if (s -> size == 0) {
        return printf("The set is empty.\n");
    }

    int i = 0;
    int count = 0;

    while (count < s -> size) {
        if (s -> values[i / 8] & (1 << (i % 8)) != 0) {
            printf("%d ", i);
            count++;
        }

        i++;
    }
}
