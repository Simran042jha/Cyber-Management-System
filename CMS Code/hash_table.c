#include "hash_table.h"

size_t hash(size_t key, size_t table_size) {
    return key % table_size;
}
size_t _insert_user(Hashtable* table, size_t usr_id, const char* usr_name, ArrTime arrivaltm)
{
    int hashed = hash(usr_id, table->size);
    if (table->table_ptr[hashed] == NULL)
    {
        table->count += 1;
        table->table_ptr[hashed] = (data*)malloc(sizeof(data));
        table->table_ptr[hashed]->id = usr_id;
        strncpy(table->table_ptr[hashed]->usrname, usr_name, 11);
        table->table_ptr[hashed]->arrivalTime = arrivaltm;
        table->table_ptr[hashed]->next = NULL;
    }
    else
    {
        data* _dat = table->table_ptr[hashed];
        while (_dat->next != NULL)
        {
            if (_dat->id == usr_id)
            {
                printf("ERROR:User already exists\n");
                return 1;
            }
            _dat = _dat->next;
        }
        table->count += 1;
        _dat->next = (data*)malloc(sizeof(data));
        _dat->next->id = usr_id;
        strncpy(_dat->next->usrname, usr_name, 11);
        _dat->next->arrivalTime = arrivaltm;
        _dat->next->next = NULL;
        
    }
    return 0;
}
data _search_user(Hashtable*  table, size_t usr_id)
{
    int hashed = hash(usr_id, table->size);
    if (table->table_ptr[hashed] == NULL)
    {
        return (data) { usr_id, "", (ArrTime) { -1, -1, -1, -1 }, NULL};
    }
    else 
    {
        data* _dat = table->table_ptr[hashed];
        while (_dat != NULL)
        {
            if (_dat->id == usr_id)
            {
                return *_dat;
            }
            _dat = _dat->next;
        }
        return (data) { usr_id, "", (ArrTime){-1,-1,-1,-1}, NULL };
    }
    
}
size_t _delete_user(Hashtable* table, size_t usr_id, int mode)
{
    int hashed = hash(usr_id,table->size);

    data usr_dat = _search_user(table, usr_id);
    if (strcmp(usr_dat.usrname, "") == 0)
    {
        printf("\n\t\t\t\tNo data associated with user id: %d", usr_id);
        return 1;
    }
    else
    {
        data* _dat = table->table_ptr[hashed];
        data* temp;
        while (_dat->next != NULL)
        {
            if (_dat->id == usr_id)
                break;
            _dat = _dat->next;
        }
        temp = _dat->next;
        if (temp != NULL)
        {
            _dat->id = _dat->next->id;
            strncpy(_dat->usrname, _dat->next->usrname, 11);
            _dat->arrivalTime = _dat->next->arrivalTime;
            _dat->next = _dat->next->next;
            free(temp);
        }
        else
        {
            free(_dat);
            table->table_ptr[hashed] = NULL;
        }
        table->count -= 1;
        if (mode == 0)
        {
            printf("\n\n\t\t\t\tRecord with user id: %d deleted successfully", usr_id);
        }
        return 0;
    }
}
int _show(Hashtable* table)
{
    int duration, tothr, totmin;
    time_t mytime;
    struct tm* current_time;
    mytime = time(NULL);
    current_time = localtime(&mytime);
    if (table != NULL)
    {
        if (table->count != 0)
        {
            for (size_t i = 0; i < table->size;i++)
            {
                data* _dat = table->table_ptr[i];
                while (_dat != NULL)
                {
                    printf("\n\n\t\t\t    %d \t\t\t%s \t\t\t%02d/%02d/%d \t%02d:%02d", _dat->id, _dat->usrname, _dat->arrivalTime.day, _dat->arrivalTime.mnth, _dat->arrivalTime.yr, _dat->arrivalTime.hr, _dat->arrivalTime.min);
                    tothr = (((current_time->tm_hour * 60) + (current_time->tm_min)) - ((_dat->arrivalTime.hr * 60) + _dat->arrivalTime.min));
                    duration = tothr / 60;
                    totmin = tothr - (duration * 60);
                    printf("\t%02dHr:%02dMin", duration, totmin);
                    _dat = _dat->next;
                }
            }
        }
        else
        {
            printf("\n\n\t\t\t\t\t\tNo data found in table!!\n");
            return 1;
        }
    }
    else
    {
        printf("\n\t\t\t\tERROR:Create table first\n");
        return 1;
    }
    return 0;
}
Hashtable* create_hashtable(size_t size)
{
    static Hashtable* table = NULL;
    if (table == NULL)
    {
        table = (Hashtable*)malloc(sizeof(Hashtable));
        table->size = size;
        table->table_ptr = (data**)malloc(sizeof(data*) * size);
        for (size_t i = 0; i < table->size;i++)
        {
            table->table_ptr[i] = NULL;
        }
        table->count = 0;
        table->insert_user = _insert_user;
        table->delete_user = _delete_user;
        table->search_user = _search_user;
        table->show = _show;
    }
    return table;
}
void delete_hashtable(Hashtable* table)
{
    for (size_t i = 0; i < table->size;i++)
    {
        while (table->table_ptr[i] != NULL)
        {
            _delete_user(table, table->table_ptr[i]->id, 1);
        }
        free(table->table_ptr[i]);
  
    }
    free(table->table_ptr);
    free(table);

}