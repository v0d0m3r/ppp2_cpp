#include "../../bstroustrup_code/std_lib_facilities.h"

class Token {
public:
        char kind;		// Разновидность лексемы
        double value;	// Для чисел: значение
        Token(char ch)    				// Получает лексему из символа (+, -, * и т.д.)
            :kind(ch), value(0) { }
        Token(char ch, double val)     	// Формирует лексему парой "8" и число
            :kind(ch), value(val) { }
};

class  Token_stream
{
public:
	 Token_stream();		// Создает объект класса Token_stream,
	 						// считывающий данные из потока cin
	 Token get();			// Получает объект Token из потока 
	 void putback(Token t); // Возвращает Token обратно в поток
private:
	bool full; 				// Имеется ли лексема в буфере?
	Token buffer; 			// Здесь хранится лексема после
							// вызова putback()
};

Token_stream::Token_stream()
:full(false), buffer(0)    // Нет Token в буфере
{
}

void Token_stream::putback(Token t)
{
	if (full) error("буфер заполнен!");	
	buffer = t; 	// Копируем t в буфер
	full = true;	// Буфер заполнен
}

Token Token_stream::get()
{
	if (full) {			// Есть готовый объект Token?
		full = false;	// Убираем его из буфера и возвращаем
		return buffer;
	}

	Token t{' '};
	char ch;
	cin >> ch;			// >> пропускает пробельные символы
	switch (ch) {
	case ';':		// для печати
	case 'q':		// для выхода	
	case '(': case ')': case '+':
	case '-': case '*': case '/':
		t = Token(ch);	// Символ представляет сам себя
		break;
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{
			cin.putback(ch);		// Возвращаем цифру во входной поток
			double val;
			cin >> val;				// Считываем число с плавающей точкой
			t = Token('8',val); 	// '8' означает лексему число
			break;
	}
	default:
		error("неверная лексема");
	}
	return t;
}

Token_stream ts;
double expression();
double term();
double primary();

int main()
{
	try {
		cout << "Введите выражение (разрешены +, -, * и /): ";
		double val = 0.00;
		while (cin) {
			Token t = ts.get();
			if (t.kind == 'q') break;
			if (t.kind == ';') 
				cout << '=' << val  << '\n';
			else
				ts.putback(t);			
			val = expression();
		}			
	}
	catch (exception& e) {
		cerr << "\nОшибка: " << e.what() << '\n';
		keep_window_open();
		return 1;
	}
	catch (...) {
		cerr << "Неизвестное исключение!\n";
		keep_window_open();
		return 2;
	}
	return 0;
}

double expression()
{
	double left = term();		// Считываем и вычисляем Терм
	Token t = ts.get();			// Получаем следующую лексему
	for (;;) {
		switch (t.kind) {
		case '+':
			left += term();		// Вычисляем терм и суммируем
			t = ts.get();
			break;
		case '-':
			left -= term();		// Вычисляем терм и вычитаем
			t = ts.get();
			break;
		default:
			ts.putback(t);
			return left;		// Конец символов + и - нет
		}						// Возвращаем ответ
	}
}

double term()
{
	double left = primary();		// Считываем и вычисляем первичное_выражение
	Token t = ts.get();				// Получаем следующую лексему
	for (;;) {
		switch (t.kind) {
		case '*':
			left *= primary();		// Вычисляем первичное_выражение и умножаем
			t = ts.get();
			break;
		case '/':
			{
				double d = primary();
				if (d == 0)	error("деление на нуль");
				left /= d;			// Вычисляем первичное_выражениеи и делим
				t = ts.get();
				break;
			}				
		default:
			ts.putback(t);
			return left;			// Конец символов * и / нет
		}							// Возвращаем ответ
	}
}

double primary()
{
	Token t = ts.get();				// Получаем следующую лексему
	double value = 0;
	switch (t.kind) {		
	case '(':
		{
			value = expression();
			t = ts.get();			
			if (t.kind != ')')	error("требуется \')\'");
			break;
		}	
	case '8':					// Используем восьмерку для представления числа
		value = t.value;		// Возвращаем значение числа
		break;
	default:
		error("требуется первичное_выражение");
	}
	return value;
}
