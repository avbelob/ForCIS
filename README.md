Белобородова Анна, группа Б05-823
Я выбрала первую задачу (Написать компьютерного соперника для игры).
Суть:
Мы подсчитываем вероятность наличия бомбы в каждой клетке 
(для этого для каждого соседа открытой клетки с числом приплюсовываем вероятность, что там есть бомба: это значение на клетки делить на количество открытых соседей).
Выбираем клетку с наименьшей вероятностью среди возможных и с наибольшей ценностью, открываем её.
