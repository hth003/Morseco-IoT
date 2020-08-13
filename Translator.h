

String alphabet = "**ETIANMSURWDKGOHVF*L*PJBXCYZQ**54*3***2**+****16=/*****7***8*"; 

String convertC2M(int decimal) {
  /* The alphabet is pass off from morse code binary tree in preorder, where left is dot and right is dash.
  Input of this function is the index of the letter in the alphabet, which is then convert to binary 
  and omit the first digit to get morse code representation.*/
  String letter;
	int binary[32]; 
	// counter for binary array 
  int i = 0;
	while (decimal > 0) { 
        // storing remainder in binary array 
        if (decimal!=1){
            binary[i] = decimal % 2; 
            i++; }
        decimal = decimal / 2; 
    } 
  // add the corresponding dash or dot in reverse order 
  for (int j = i - 1; j >= 0; j--) 
    (binary[j]==1)? letter.concat("-") : letter.concat("."); 
  return letter;
}

String morseEncoder(char c) {
  /* Search for letter in the alphabet and return the morse code string*/
  String m_char;
	if (c >= 'a' && c <= 'z') c -= 32; // convert to uppercase
	if (c < 'A' || c > 'Z') return ""; //reject character that is not in the alphabet
	int i = 0;
	//search for corresponding letter in alphabet
	while (alphabet[i] != c){
	  i++;
	}
	return convertC2M(i);
}

String string2Morse(String input){
  /*Traverse the sentence to translate one letter at a time. Return the string with encoded morse code*/
  String m_str;
  //add a space between letters and 2 space between words 
  for (int i = 0; i <input.length(); i++)
  {
    m_str.concat(morseEncoder(input.charAt(i)));
    if (isSpace(input.charAt(i))){
      m_str.concat("  ");
    }else{
      m_str.concat(" ");
    }
  }
  return m_str;
}

/*****************************************************/
String morseDecoder(String m_str) {
  /* Find the pointer position that point to the letter that corresponse to the respective morsecode */
  String txt;
  int ptr = 0;
  for (int i = 0; i<m_str.length();i++){
    if (m_str.charAt(i) == '.') {
      ptr = (2*ptr) + 1;
    } else if (m_str.charAt(i) == '-'){
      ptr = (2*ptr) + 2;
    } else if (m_str.charAt(i) == ' '){
      if (m_str.charAt(i-1) == ' '){
        txt.concat(" ");
      } else if (i>0){
        txt.concat(alphabet[ptr+1]);
      }
      ptr = 0;
    }
  }
  return txt;
}

