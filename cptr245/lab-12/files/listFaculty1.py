#!/usr/bin/env python3
import psycopg2

def main():
  print("Content-type:text/html\r\n\r\n")
  print('<html>')
  print('<head>')
  print('<title>List of CS Faculty</title>')
  print('</head>')
  print('<body>')

  conn = None
  try:
    conn = psycopg2.connect(dbname="cptr245")
    with conn.cursor() as curs:
      curs.execute('SELECT version from "DbVersion"')
      row = curs.fetchone()
      dbVersion = row[0]
      if (dbVersion != 1):
        raise Exception('Wrong Database version:', dbVersion)

    print('<h3>CS Faculty:</h3>')
    print('<ul>')
    with conn.cursor() as curs:
      curs.execute('SELECT name from "Faculty" ORDER BY name')
      for each in curs.fetchmany(99):
        print('<li>' + each[0] + '</li>')
    print('</ul>')

  except (Exception, psycopg2.DatabaseError) as error:
    print(error)
  finally:
    if conn is not None:
        conn.close()

  print('</body>')
  print('</html>')


if __name__ == '__main__':
    main()
