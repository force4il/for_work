# скачать библиотеку pymysql
import pymysql 
from lint.config import *

# в блоке try except создаем соединение с базой данных 
try:
    connection = pymysql.connect(
        host=host,
        port=3306,
        user=user,
        password=password,
        database=db_name,
        cursorclass=pymysql.cursors.DictCursor
    )
    print('Successfully connected')
    print('-' * 20)

    try:
        # создаём объект курсор для выполнения sql запросов 
        cursor = connection.cursor()
        create_table_query = "CREATE TABLE `users` (" \
        "id int AUTO_INCREMENT, " \
        "name VARCHAR(32), " \
        "password VARCHAR(32), " \
        "email VARCHAR(32), " \
        "PRIMARY KEY (id));"
        cursor.execute(create_table_query) # отправляем запрос
        print('Table is created')

        with connection.cursor() as cursor:
            insert_query = "INSERT INTO `users` (name, password, email) VALUES('Anna', '1223', 'someone@gmail.com');"
            cursor.execute(insert_query)
            connection.commit() #сохраняем переданные данные в дб
        print('the data has been successfully entered')

        cursor = connection.cursor()
        cursor.execute("SELECT * FROM `users`")
        rows = cursor.fetchall() #сохраняем в переменную все строки таблицы
        for row in rows:
            print(row)
        with connection.cursor() as cursor:
            update_query = "UPDATE `users` SET password = 'Misha' WHERE name = 'Anna';"
            cursor.execute(update_query)
            connection.commit()

        cursor = connection.cursor()
        drop_table = "DROP TABLE `users`;"
        cursor.execute(drop_table)

    # блок finally нужен для 100% закрытия соединения для избежания утечки данных 
    finally:
        connection.close()

except Exception as ex:
    print('Connect error: ', ex)