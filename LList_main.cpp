#include <iostream>
#include "LinkedList.cpp"

using namespace std;

void see(LinkedList<int> L) {
	for (int i = 0; i < L.Length(); i++)
		cout << L.At(i) << endl;
}

int main()
{
	LinkedList<int> L;
//	L.undo();
	L.Append(9);
	L.Append(10);
	L.Append(11);
	cout << "Before : \n";
	see(L);
	L.DeleteAt(1);
	see(L);
	L.undo();
	see(L);
	L.Append(13);
	cout << "Added 11, 13 : \n";
	L.undo();
	//L.InsertAt(1,100);
	//L.DeleteAt(3);

	return 0;
}