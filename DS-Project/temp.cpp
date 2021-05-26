//#include<iostream>
//#include<algorithm>
//#include<string>
//using namespace std;
//void LOL(string &str){
//	for (unsigned i = 0; i < str.size(); i++)
//		str[i] = tolower(str[i]);
//}
//double fun(string s1, string s2)
//{
//	LOL(s1), LOL(s2);
//	double sum = 0;
//	for (int i = 0; i < (int)s1.size(); i++){
//		if (i == (int)s2.size()){
//			if (s1[i] == s2[i - 1])
//				sum += 0.5;
//			break;
//		}
//		if (s1[i] == s2[i])
//			sum++;
//		else if (s1[i] == s2[i + 1] || s1[i] == s2[abs(i - 1)])
//			sum += 0.5;
//	}
//	return(sum / max(s1.size(), s2.size()));
//}
//
//void main()
//{
//	string s1, s2;
//	cin >> s1 >> s2;
//	cout << fun(s1, s2) << "\n";
//}