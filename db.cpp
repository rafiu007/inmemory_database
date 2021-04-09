#include<bits/stdc++.h>
using namespace std;

class Row {
    public:
        string rowid;
        map<string,string>columnValue;
    
    Row(string rowid, map<string,string>columnValue){
        this->rowid=rowid;
        this->columnValue=columnValue;
    }

    map<string,string> getColumnValue(){
        return columnValue;
    }

    void setColumnValue(map<string,string> columnValue){
        this->columnValue= columnValue;
    }

    string getrowid(){
        return rowid;
    }

    string setrowid(string rowid){
        this->rowid =rowid;
    }

    //prints contents of a row
    void printrow(){
        cout<<rowid<<" ";

        for(auto a:columnValue){
            cout<<a.second<<" ";
        }

        cout<<endl;
    }

};


class Table {
    public:
        string tableName;
        map<string,Row>rows;
        map<string,int>maxval;
        map<string,int>minval;
        map<string,int>maxval_for_string;
        map<string,int>not_nul;

        Table(string name){
            this->tableName=name;
            this->rows= map<string,Row>();
        }

        //utility cuntion to convert string to integer
        int valfromstring(string s){
            int value=0;
            int i=0;
            while(i<s.length()){
                value+=pow(10,i);
                i++;
            }

            return value;
        }

        //utility function to check
        string returnvalue(string s){
            for(int i=0;i<s.length();i++){
                if(s[i]>='0' && s[i]<'9'){
                    return "Integer";
                }
            }

            return "String";
        }

        //utility function to check constraints before inserting into table
        bool checkconstraints(map<string,string>columnsMap){
            bool returnval;
            //check constraints for string and integer
            for(auto a:columnsMap){
                if(returnvalue(a.second)=="String"){
                    if(a.second.length()>maxval_for_string[a.first]){
                        cout<<a.first<<"fails to pass contraints"<<endl;
                        returnval= false;
                    }
                    else{
                        returnval= true;
                    }
                }
                else{
                    int value=valfromstring(a.second);

                    if(value<=maxval[a.first] && value>=minval[a.first]){
                        returnval= true;
                    }
                    else{
                        cout<<a.first<<"fails to pass contraints"<<endl;
                        returnval= false;
                    }
                }
            }
            //check not null contraint

            for(auto a:not_nul){
                if(a.second ==1 && columnsMap.find(a.first)==columnsMap.end()){
                    returnval=true;
                }
                else{
                    cout<<a.first<<"hash not-null constraint"<<endl;
                    returnval=false;
                }
            }

            return returnval;
        }

        //function to enter a row in a given table
        void insertentry(string rowid, map<string,string>columnsMap){
            if(rows.find(rowid)==rows.end()){
                if(checkconstraints(columnsMap)){
                    Row row = Row(rowid,columnsMap);
                    cout<<"row created"<<endl;
                }
            }
            else{
                cout<<"Primary key already exists"<<endl;
            }
        }

        void setMaxval(int maxval,string columnName){
            this->maxval[columnName]=maxval;
        }

        void setMinval(int minval,string columnName){
            this->minval[columnName]=minval;
        }

        void setMaxval_for_string(int maxval,string columnName){
            this->maxval_for_string[columnName]=maxval;
        }

        void setnot_null(string columnName){
            this->not_nul[columnName]=1;
        }

        //prints a row one by one
        void printall(){
            for(auto a:rows){
                a.second.printrow();
            }
        }

};

map<string,int>maxallowedvalues;
map<string,int>minallowedvalues;
map<string,Table>tablehash;


//function to check if table with same name has been created
bool createtable(string tablename){
    if(tablehash.find(tablename)==tablehash.end()){
     return true;   
    }

    return false;
}

//set maximum limits for a datatype
void setmaxallowedvalues(string datatypename,int value){
    maxallowedvalues[datatypename]=value;
    return;
}

void setminallowedvalues(string datatypename,int value){
    minallowedvalues[datatypename]=value;
    return;
}

//function to delete a table
//void deleteTable(Table* tab){
//    tablehash.erase(*tab.tablename);
//    delete tab;
//}


int main(){

    maxallowedvalues["code"]=20;
    maxallowedvalues["points"]=1024;
    minallowedvalues["points"]=-1024;


    Table interview = Table("interviwe");

    interview.setMaxval(1024,"points");
    interview.setMinval(-1024,"points");
    interview.setMaxval_for_string(20,"code");

    map<string,string>mp;
    mp["code"]="HeyIamacfg";
    mp["points"]="10000000";


    interview.insertentry("1",mp);

    interview.printall();

    return 0;
}