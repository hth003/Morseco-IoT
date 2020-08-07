
String alphabet = "**ETIANMSURWDKGOHVF*L*PJBXCYZQ**"; 

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
  // printing binary array in reverse order 
  for (int j = i - 1; j >= 0; j--) 
    (binary[j]==1)? letter.concat("-") : letter.concat("."); 
  return letter;
}

String morseEncoder(char c) {
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
  String m_str;
  //add a space between letters and 3 space between words 
  for (int i = 0; i <input.length(); i++)
  {
    m_str.concat(morseEncoder(input.charAt(i)));
    if (isSpace(input.charAt(i))){
      m_str.concat("   ");
    }else{
      m_str.concat(" ");
    }
  }
  return m_str;
}
