
bool contains(const String &s, const String &search) {
  int index = s.indexOf(search);
  if(index != -1) {
    bool beforeIsCorrect = true;
    if(index > 0) {
      int beforeLength = index;
      if(beforeLength > search.length()){
        beforeIsCorrect = false;
      }else{
        String beforeString = s.substring(0, beforeLength);
        beforeIsCorrect = search.endsWith(beforeString);
      }
    }
    if(beforeIsCorrect){
      int afterIndex = index + search.length();
      int afterLength = s.length() - afterIndex;
      if(afterLength>0){
        String afterString = s.substring(afterIndex);
        if(afterLength >= search.length()) {
          return contains(afterString, search); 
        }else{
          return search.startsWith(afterString);
        }
      }else{
        return true;
      }
    }else{
      return false;
    }
  }else{
    return false;
  }
}

struct Test{
  String whereToSearch;
  String whatToSearch;
  bool expectedResult;

  Test(String where, String what, bool ex):whereToSearch(where), whatToSearch(what), expectedResult(ex){}
};

void setup() {
  Serial.begin(9600); 
  
  Test tests[]={
    Test("11111111111111", "01", false),
    Test("111111111111110", "01", false),
    Test("111111111111101", "01", false),
    Test("111111111111010", "01", false),
    Test("111111111010101", "01", false),
    Test("101010101010101", "01", true),
    Test("00110011001100110", "0011", true),
    Test("00110011101100110", "0011", false),
    Test("00110011001100111", "0011", false),
  };
  int testsCount = sizeof(tests) / sizeof(Test);
  for(int i=0; i<testsCount; ++i) {
    Test &test = tests[i];
    bool testAccepted = test.expectedResult == contains(test.whereToSearch, test.whatToSearch);
    Serial.print("testAccepted[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.print(testAccepted);
    Serial.println();
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
