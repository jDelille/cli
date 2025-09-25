#ifndef TEMPLATES_H
#define TEMPLATES_H

void create_template(
    const char *language, 
    const char *templateName
);

void create_file_from_template(
    const char *filename, 
    const char *templateName
);

void list_templates();

#endif