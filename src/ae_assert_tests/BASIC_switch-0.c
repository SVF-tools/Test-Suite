//
// Created by Jiawei Wang on 1/17/22.
//


int main() {
    int x, y;
    x = 1;
    y = 0;
    char cond = 'a';
    switch (cond)
    {
        case 'a':
            x += 1;
            break;
        case 'bb':
            x += y;
        case 'c':
            x -= y;
        default:
            x++;
            y++;
            break;
    }
    svf_assert(x >= y);
    return 0;
}