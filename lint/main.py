import sqlite3

with sqlite3.connect('test.db') as conn:
    cursor = conn.cursor()
    cursor.execute('''
    CREATE TABLE IF NOT EXISTS students (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        name TEXT NOT NULL,
        age INTEGER,
        mark REAL
    )
    ''')

    cursor.execute('DELETE FROM students')

    students_data = [
        ('Анна Иванова', 19, 4.8),
        ('Борис Петров', 20, 4.5),
        ('Виктория Сидорова', 18, 4.9),
        ('Глеб Смирнов', 21, 4.2)
    ]

    cursor.executemany('INSERT INTO students (name, age, mark)'
                       'VALUES (?, ?, ?)', students_data)
    print("Добавлены студенты: ")
    pattern = ", "
    for st in students_data:
        if (st == students_data[-1]):
            pattern = "\n"
        print(st[0], end=pattern)

    cursor.execute('UPDATE students SET mark = 5.0 '
                   'WHERE name = "Анна Иванова"')

    print("\nВсе студенты в бд: ")
    cursor.execute('SELECT * FROM students')
    for i in cursor.fetchall():
        print(f"id: {i[0]}, name: {i[1]}, age: {i[2]}, mark: {i[3]}")

    print("\nСтуденты с оценкой выше 4.5: ")
    cursor.execute('SELECT name, mark FROM students WHERE mark > 4.5')
    for name, mark in cursor.fetchall():
        print(name, mark)

    cursor.execute('SELECT AVG(mark), MAX(mark), MIN(mark) FROM students')
    avg_mark, max_mark, min_mark = cursor.fetchone()
    cursor.execute("SELECT name FROM students WHERE mark = :min_mark",
                   {"min_mark": min_mark})
    name_min = cursor.fetchone()
    cursor.execute("SELECT name FROM students WHERE mark = :max_mark",
                   {"max_mark": max_mark})
    name_max = cursor.fetchone()
    print("\nСтатистика по баллу:")
    print(f"Средний балл: {avg_mark:.2f}")
    print(f"Максимальный балл: {max_mark} ({name_max[0]})")
    print(f"Минимальный балл: {min_mark} ({name_min[0]})")

    cursor.execute('SELECT * FROM students WHERE mark < 4.3')
    del_students = cursor.fetchall()
    cursor.execute('DELETE FROM students WHERE mark < 4.3')
    print("\nУдалены студенты с оценкой ниже 4.3:")
    for i in del_students:
        print(f"id: {i[0]}, name: {i[1]}, age: {i[2]}, mark: {i[3]}")

    cursor.execute('SELECT name, mark FROM students')
    print("\nОставшиеся студенты:")
    for name, mark in cursor.fetchall():
        print(f"{name}: {mark}")

    conn.commit()
