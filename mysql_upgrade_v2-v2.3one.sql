ALTER TABLE admins ADD COLUMN access BIGINT unsigned DEFAULT '4294963199' NOT NULL;

CREATE TABLE safelist ( 
	id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, 
	server TEXT NOT NULL, 
	name TEXT NOT NULL
);