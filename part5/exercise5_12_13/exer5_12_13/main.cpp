//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//-----------------------------------------------------------------------------

constexpr int count_digit = 4; // Необходимое колличество
                               // цифр игры "Быки и Коровы"
//-----------------------------------------------------------------------------

vector<int> check_inp_data(string data)
{
    int current_digit = 0;
    vector<int> good_data;
    for (size_t i=0; i<data.size(); ++i)
    {
        switch (data[i]) {
            case '0':
                current_digit = 0;
                break;
            case '1':
                current_digit = 1;
                break;
            case '2':
                current_digit = 2;
                break;
            case '3':
                current_digit = 3;
                break;
            case '4':
                current_digit = 4;
                break;
            case '5':
                current_digit = 5;
                break;
            case '6':
                current_digit = 6;
                break;
            case '7':
                current_digit = 7;
                break;
            case '8':
                current_digit = 8;
                break;
            case '9':
                current_digit = 9;
                break;
            default:
                error("Недопустимые цифры в числе!!!");
                break;
        }
        good_data.push_back(current_digit);
    }
    return good_data;
}

//-----------------------------------------------------------------------------

vector<int> make_secr_digit(vector<int> data, int random)
{
    int temp_rand = random;
    srand(random);
    bool add_rand = true;
    for (;;)
    {
        random = randint(10);
        for (size_t j=0; j<data.size(); ++j)
            if (data[j] == random)
                add_rand = false;

        if (add_rand)
            data.push_back(random);
        else
        {
            temp_rand++;
            srand(temp_rand);
            add_rand = true;
        }
        if (data.size() == count_digit)
            break;
    }
    return data;
}

//-----------------------------------------------------------------------------

int main()
try {
    vector<int> secret_digits;  // Загаданная компьютером последовательность
                                // из 4 цифр от (0 до 9)
    int random = 0;
    cout << "Введите число от (от 0 до 9):\n";
    cin >> random;
    if (!cin)
        error("Вы ввели нецелое число!");
    else if (random>=0 && random<=9)
        secret_digits = make_secr_digit(secret_digits, random);
    else
        error("Вы ввели неправильное случайное число!");

    for (size_t i=0; i<secret_digits.size(); ++i)
        cout << ":" << secret_digits[i];
    cout << '\n';

    vector<int> user_digits;
    int buls_count = 0;
    int cows_count = 0;

    cout << "Введите число (из 4 цифр от 0 до 9), "
         << "которое вы думаете загадал компьютер:\n";
    for (string input_variant; cin >> input_variant; )
    {
        if (input_variant.size() != count_digit)
            error("Неверное колличество цифр в числе!!!");
        user_digits = check_inp_data(input_variant);

        for (int i=0; i<count_digit; ++i)
        {
            if (secret_digits[i] == user_digits[i])
                ++buls_count;
            else
                for (int j=0; j<count_digit; ++j)
                    if(secret_digits[j]==user_digits[i])
                        ++cows_count;
        }
        if (buls_count == count_digit)
        {
            cout << "Поздравляю у Вас 4 быка\n";
            cout << "Новая игра!! Введите число от (от 0 до 9):\n";
            cin >> random;
            if (!cin)
                error("Вы ввели нецелое число!");
            else if (random>=0 && random<=9)
                secret_digits = make_secr_digit(secret_digits, random);
            else
                error("Вы ввели неправильное случайное число!");
        }
        cout << "Колличество быков: " << buls_count
             << " Колличество коров: " << cows_count
             << "\nВведите повторно число (из 4 цифр от 0 до 9), "
                "которое вы думаете загадал компьютер:\n";
        user_digits.clear();
        buls_count = 0;
        cows_count = 0;
    }

    keep_window_open();
    return 0;
}
catch (exception& e) {
    cerr << e.what() << '\n';
    keep_window_open();
    return -1;
}
catch (...) {
    cerr << "exiting\n";
    keep_window_open();
    return -2;
}

//-----------------------------------------------------------------------------
