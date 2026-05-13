#include <stdio.h>
#include <string.h>

#include "snekobject.h"

void refcount_dec(snek_object_t *obj) {
    if(obj == NULL) return NULL;
    obj->refCount--;
    
    if(obj->refCount == 0) {
        refcount_free(obj);
    }
}

void refcount_free(snek_object_t *obj) {
    if(obj == NULL) return NULL;
    switch (obj->kind) {
        case INTEGER:
        case FLOAT: break;
        case STRING: {
            free(obj->data.v_string);
            break;
        }
        case VECTOR3: {
            refcount_dec(obj->data.v_vector3.x);
            refcount_dec(obj->data.v_vector3.y);
            refcount_dec(obj->data.v_vector3.z);
            break;
        }
        case ARRAY: {
            snek_array_t arr = obj->data.v_array;
            for (size_t i = 0; i < arr.size; i++)
            {
                refcount_dec(arr.elements[i]);
            }
            free(obj->data.v_array.elements);
            break;
        }
    }
    free(obj);
}

void refcount_inc(snek_object_t *obj) {
    if(obj == NULL) return NULL;
    obj->refCount++;
}

snek_object_t *_new_snek_object() {
    snek_object_t *obj = malloc(sizeof(snek_object_t));
    if(obj == NULL) return NULL;

    obj->refCount = 1;
    return obj;
}

snek_object_t *snek_add(snek_object_t *a, snek_object_t *b) {
    if(a == NULL || b == NULL) return NULL;
    switch (a->kind) {
    case INTEGER:
        switch (b->kind) {
            case INTEGER: return new_snek_integer(a->data.v_int + b->data.v_int);
            case FLOAT: return new_snek_float((float)a->data.v_int + b->data.v_float);
            default: return NULL;
        }
    
    case FLOAT:
        switch (b->kind) {
            case INTEGER: return new_snek_float(a->data.v_float + (float)b->data.v_int);
            case FLOAT: return new_snek_float(a->data.v_float + b->data.v_float);
            default: return NULL;
        }

    case STRING:
        if(b->kind != STRING) return NULL;
        size_t newLen = snek_length(a->data.v_string) + snek_length(b->data.v_string) + 1;
        char *newStr = calloc(newLen, sizeof(char *));
        if(newStr == NULL) return NULL;
        strcat(newStr, a->data.v_string);
        strcat(newStr, b->data.v_string);
        snek_object_t *snekString = new_snek_string(newStr);
        free(newStr);
        return snekString;

    case VECTOR3:
        if(b->kind != VECTOR3) return NULL;
        return new_snek_vector3(snek_add(a->data.v_vector3.x, b->data.v_vector3.x),
                                snek_add(a->data.v_vector3.y, b->data.v_vector3.y), 
                                snek_add(a->data.v_vector3.z, b->data.v_vector3.z));
    
    case ARRAY:
        if(b->kind != ARRAY) return NULL;
        snek_array_t *snekObjArr = new_snek_array(a->data.v_array.size + b->data.v_array.size);
        int index = 0;
        while(index < a->data.v_array.size) {
            snek_array_set(snekObjArr, index, snek_array_get(a, index));
            index++;
        }
        while(index < b->data.v_array.size) {
            snek_array_set(snekObjArr, index, snek_array_get(b, index));
            index++;
        } 
        return snekObjArr;

    default: 
        return NULL;
    }
}

int snek_length(snek_object_t *obj) {
    if(obj == NULL) return -1;
    switch (obj->kind)
    {
    case INTEGER: 
        return 1;
    case FLOAT:
        return 1;
    case STRING:
        return strlen(obj->data.v_string);
    case VECTOR3:
        return 3;
    case ARRAY:
        return obj->data.v_array.size;
    default:
        return -1;
    }
}

bool snek_array_set(snek_object_t *snek_obj, size_t index, snek_object_t *value) {
    if(snek_obj == NULL || value == NULL) return false;
    if(snek_obj->kind != ARRAY) return false;
    if(snek_obj->data.v_array.size <= index) return false;

    refcount_inc(value);
    if(snek_obj->data.v_array.elements[index] != NULL) {
        refcount_dec(snek_obj->data.v_array.elements[index]);
    }

    snek_obj->data.v_array.elements[index] = value;
    return true;
}

snek_object_t *snek_array_get(snek_object_t *snek_obj, size_t index) {
    if(snek_obj == NULL) return NULL;
    if(snek_obj->kind != ARRAY) return NULL;
    if(snek_obj->data.v_array.size <= index) return false;

    return snek_obj->data.v_array.elements[index];
}

snek_object_t *new_snek_array(size_t size) {
    snek_object_t *snekObject = malloc(sizeof(snek_object_t));
    if(snekObject == NULL) { return NULL; }

    snekObject->kind = ARRAY;
    snek_object_t **elements = calloc(size, sizeof(snek_object_t *));
    if(elements == NULL) return NULL;
    
    snek_array_t array = {.size = size, .elements = elements};
    snekObject->data.v_array = array;

    return snekObject;
}

snek_object_t *new_snek_vector3(snek_object_t *x, snek_object_t *y, snek_object_t *z) {
    if (x == NULL || y == NULL || z == NULL) {
        return NULL;
    }
    snek_object_t *obj = _new_snek_object();
    if (obj == NULL) {
        return NULL;
    }
    obj->kind = VECTOR3;
    refcount_inc(x);
    refcount_inc(y);
    refcount_inc(z);
    obj->data.v_vector3 = (snek_vector_t){.x = x, .y = y, .z = z};
    return obj;
}

snek_object_t *new_snek_string(char *value) {
    snek_object_t *snekObject = malloc(sizeof(snek_object_t));
    if(snekObject == NULL) { return NULL; }

    snekObject->kind = STRING;
    snekObject->data.v_string = malloc(strlen(value) + 1);
    if(snekObject->data.v_string == NULL) return NULL;
    strcpy(snekObject->data.v_string, value);

    return snekObject;
}

snek_object_t *new_snek_float(float value) {
    snek_object_t *snekObject = malloc(sizeof(snek_object_t));
    if(snekObject == NULL) return NULL;

    snekObject->kind = FLOAT;
    snekObject->data.v_float = value;

    return snekObject;
}

snek_object_t *new_snek_integer(int value) {
    snek_object_t *snekObject = malloc(sizeof(snek_object_t));
    if(snekObject == NULL) return NULL;

    snekObject->kind = INTEGER;
    snekObject->data.v_int = value;

    return snekObject;
}