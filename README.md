Пономарев Артем Александрович, ФИВТ 2 курс, Б05-814, ПМФ
Задача для 1С

# 1C_A006
Problem A006
Задача А006
<p>Телефонный справочник. 


<p>Реализуйте структуру данных для хранения телефонов и фамилий клиентов.
<p>Структура должна отвечать на следующие запросы:
<p>Найти фамилию клиента по номеру телефона.
<p>Найти номер телефона по фамилии.
<p>Добавить пару “телефон - фамилия”.
<p>По первым нескольким цифрам номера получить список фамилий с подходящими номерами.
<p>Дополнительно, если успеете:
<p>По номеру со случайными пропусками цифр в середине номера получить список фамилий с подходящими номерами. Например, по номеру 89*633*71*3.

<p>Idea: Lower memory usage (~10^11 numbers is quiet alot!), using a tree. Had to chose between efficient search by number and by surname. 


# Solved:
<p>The structure can give the number by the surname and vice versa, add contacts and get the vector<string> of suitable surnames by the first digits.
  
  
  
  Asymptotics:
  Time:
    <p>Find the surname by the number - O(number.size())
    <p>Find the number by the surname - O(tree.size()) (it is actually 10^(log10(tree.size()) - suffix.size()) because of using BFS in the remaining sub-tree)
    <p>Find the surnames by the first digits - O(tree.size())
    <p>Add contact - O(number.size())
   
   Memory: approximately O(tree.size()) for the tree and BFS
   
    
    
    
Algorithm:
  <p>Base suffix tree. Nodes contain a character, is_leaf boolean, vector of pointers to the next nodes and the surname (it is empty if is_leaf is false)
  
  
    
TODO:
  <p>Implement more efficient Tree structure based on what was released (for example, compressed suffix tree and algorithms based on it. This may also help with searching by string patterns. Aho-Korasik may do https://neerc.ifmo.ru/wiki/index.php?title=%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC_%D0%90%D1%85%D0%BE-%D0%9A%D0%BE%D1%80%D0%B0%D1%81%D0%B8%D0%BA)
  <p>Make some getters const
  <p>Smart pointers!
  <p>In the case of having alot of memory it is possible to use unordered maps for everything.
  
  

