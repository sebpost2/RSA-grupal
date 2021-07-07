#include <NTL/ZZ.h>
#include <iostream>
#include "headers/RSA.h"
#include "headers/functions.h"
#include <vector>

using std::cin;
using std::cout;
using std::endl;

int main()
{

    ZZ bits, p, q, e, ea, Na, eb, Nb;
    bool WithSig;
    vector<string>Cypher;
    vector<string>DCypher;
    string alpha, sig, message;

    bits = 1024;
    alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ,.-( )abcdefghijklmnopqrstuvwxyz<>*1234567890[]";
    sig = "Sebastian Tinajeros Estrada Sebastian Gonzalo Postigo Avalos Fabian Concha Sifuentes Joaquin Casusol Escalante Frank Salas Ticona 201-10-47883 201-10-48100 201-10-47533 201-10-47494 201-10-47829 sebastian.tinajerosucsp.edu.pe sebastian.postigoucsp.edu.pe fabian.conchaucsp.edu.pe joaquin.casusolucsp.edu.pe frank.salasucsp.edu.pe";
    message="The idea of an asymmetric public-private key cryptosystem is attributed to Whitfield Diffie and Martin Hellman, who published this concept in 1976. They also introduced digital signatures and attempted to apply number theory. Their formulation used a shared-secret-key created from exponentiation of some number, modulo a prime number. However, they left open the problem of realizing a one-way function, possibly because the difficulty of factoring was not well-studied at the time.[4] Ron Rivest, Adi Shamir, and Leonard Adleman at the Massachusetts Institute of Technology, made several attempts over the course of a year to create a one-way function that was hard to invert. Rivest and Shamir, as computer scientists, proposed many potential functions, while Adleman, as a mathematician, was responsible for finding their weaknesses. They tried many approaches including knapsack-based and permutation polynomials. For a time, they thought what they wanted to achieve was impossible due to contradictory requirements.[5] In April 1977, they spent Passover at the house of a student and drank a good deal of Manischewitz wine before returning to their homes at around midnight.[6] Rivest, unable to sleep, lay on the couch with a math textbook and started thinking about their one-way function. He spent the rest of the night formalizing his idea, and he had much of the paper ready by daybreak. The algorithm is now known as RSA the initials of their surnames in same order as their paper.[7] Clifford Cocks, an English mathematician working for the British intelligence agency Government Communications Headquarters (GCHQ), described an equivalent system in an internal document in 1973.[8] However, given the relatively expensive computers needed to implement it at the time, it was considered to be mostly a curiosity and, as far as is publicly known, was never deployed. His discovery, however, was not revealed until 1997 due to its top-secret classification. Kid-RSA (KRSA) is a simplified public-key cipher published in 1997, designed for educational purposes. Some people feel that learning Kid-RSA gives insight into RSA and other public-key ciphers, analogous to simplified DES.[9][10][11][12][13] A patent describing the RSA algorithm was granted to MIT on 20 September 1983 U.S. Patent 4,405,829 Cryptographic communications system and method. From DWPIs abstract of the patent The system includes a communications channel coupled to at least one terminal having an encoding device and to at least one terminal having a decoding device. A message-to-be-transferred is enciphered to ciphertext at the encoding terminal by encoding the message as a number M in a predetermined set. That number is then raised to a first predetermined power (associated with the intended receiver) and finally computed. The remainder or residue, C, is... computed when the exponentiated number is divided by the product of two predetermined prime numbers (associated with the intended receiver). A detailed description of the algorithm was published in August 1977, in Scientific Americans Mathematical Games column.[7] This preceded the patents filing date of December 1977. Consequently, the patent had no legal standing outside the United States. Had Cockss work been publicly known, a patent in the United States would not have been legal either. When the patent was issued, terms of patent were 17 years. The patent was about to expire, on 21 September 2000, when RSA Security released the algorithm to the public domain, on 6 September 2000.[14] There are a number of attacks against plain RSA as described below.When encrypting with low encryption exponents (e.g., e  3) and small values of the m, (i.e., m <n1e) the result of me is strictly less than the modulus n. In this case, ciphertexts can be decrypted easily by taking the eth root of the ciphertext over the integers. If the same clear text message is sent to e or more recipients in an encrypted way, and the receivers share the same exponent e, but different p, q, and therefore n, then it is easy to decrypt the original clear text message via the Chinese remainder theorem. Johan Hstad noticed that this attack is possible even if the cleartexts are not equal, but the attacker knows a linear relation between them.[22] This attack was later improved by Don Coppersmith (see Coppersmiths attack).[23] Because RSA encryption is a deterministic encryption algorithm (i.e., has no random component) an attacker can successfully launch a chosen plaintext attack against the cryptosystem, by encrypting likely plaintexts under the public key and test if they are equal to the ciphertext. A cryptosystem is called semantically secure if an attacker cannot distinguish two encryptions from each other, even if the attacker knows (or has chosen) the corresponding plaintexts. As described above, RSA without padding is not semantically secure.[24] RSA has the property that the product of two ciphertexts is equal to the encryption of the product of the respective plaintexts. That is m1em2e  (m1m2)e (mod n). Because of this multiplicative property a chosen-ciphertext attack is possible. E.g., an attacker who wants to know the decryption of a ciphertext c  me (mod n) may ask the holder of the private key d to decrypt an unsuspicious-looking ciphertext c  cre (mod n) for some value r chosen by the attacker. Because of the multiplicative property c is the encryption of mr (mod n). Hence, if the attacker is successful with the attack, they will learn mr (mod n) from which they can derive the message m by multiplying mr with the modular inverse of r modulo n.[citation needed] Given the private exponent d one can efficiently factor the modulus n  pq. And given factorization of the modulus n  pq, one can obtain any private key (d,n) generated against a public key (e,n).[15] To avoid these problems, practical RSA implementations typically embed some form of structured, randomized padding into the value m before encrypting it. This padding ensures that m does not fall into the range of insecure plaintexts, and that a given message, once padded, will encrypt to one of a large number of different possible ciphertexts. Standards such as PKCS1 have been carefully designed to securely pad messages prior to RSA encryption. Because these schemes pad the plaintext m with some number of additional bits, the size of the un-padded message M must be somewhat smaller. RSA padding schemes must be carefully designed so as to prevent sophisticated attacks that may be facilitated by a predictable message structure. Early versions of the PKCS1 standard (up to version 1.5) used a construction that appears to make RSA semantically secure. However, at Crypto 1998, Bleichenbacher showed that this version is vulnerable to a practical adaptive chosen ciphertext attack. Furthermore, at Eurocrypt 2000, Coron et al.[25] showed that for some types of messages, this padding does not provide a high enough level of security. Later versions of the standard include Optimal Asymmetric Encryption Padding (OAEP), which prevents these attacks. As such, OAEP should be used in any new application, and PKCS1 v1.5 padding should be replaced wherever possible. The PKCS1 standard also incorporates processing schemes designed to provide additional security for RSA signatures, e.g. the Probabilistic fSignature Scheme for RSA (RSA-PSS). Secure padding schemes such as RSA-PSS are as essential for the security of message signing as they are for message encryption. Two USA patents on PSS were granted (USPTO 6266771 and USPTO 70360140) however, these patents expired on 24 July 2009 and 25 April 2010, respectively. Use of PSS no longer seems to be encumbered by patents.[original research] Note that using different RSA key-pairs for encryption and signing is potentially more secure.[26]";

    char input;
    std::cout<<"RSA";
    std::cout<<"\nPara Test completo (a), para Generar numeros (b), Para cifrar o descifrar(c)\n";
    std::cin>>input;

    if (input=='a'){
        std::cout<<"\nTEST COMPLETO\n";
        //nuestro abecedario y firma
        std::cout<<"\nEMISOR:\n";
        RSA Emisor(bits,alpha,sig);
        std::cout<<"\nRECEPTOR:\n";
        RSA Receptor(bits,alpha,sig);

        //claves publicas
        ea = Emisor.e;
        Na = Emisor.N;
        eb = Receptor.e;
        Nb = Receptor.N;
        WithSig = true;
        //Emisor cifra
        vector<string>Cypher = Emisor.cypherwithsignature(message, eb, Nb);
        cout << "El mensajeCifrado es: \n" << Cypher.at(0) << "\nfirma:\n" << Cypher.at(1) << endl;
        //Receptor decifra
        vector<string>DCypher = Receptor.decypherwithsignature(Cypher, ea, Na);
        cout << "\nMensaje:\n" << DCypher.at(0) << "\nfirma\n" << DCypher.at(1) << endl;
    }
//GENERADOR DE NUMEROS

    else if (input=='b'){
        std::cout<<"\nGENERANDO NUMEROS...\n";
        RSA generator(bits,alpha,sig);
    }

//CIFRANDO Y DECIFRANDO

    else if (input=='c'){
        std::cout<<"\nCifrado o descifrado\n";
        p = conv<ZZ>(""); //aqui se ingresa p predeterminada para cifrar o descifrar
        q = conv<ZZ>(""); //aqui se ingresa q predeterminado para cifrar o descifrar
        e = conv<ZZ>(""); //aqui se ingresa e predeterminada para cifrar o descifrar

        RSA testing(p, q, e, alpha, sig);

        eb=conv<ZZ>(""); //aqui se ingresa e del receptor
        Nb=conv<ZZ>(""); //aqui se ingresa N del receptor
        std::cout<<"\nCLAVES PUBLICAS DE RECEPTOR\ne: "<<eb<<"\nN: "<<Nb<<"\n";
        std::cout<<"\nPara cifrar(a), para descifrar(b)\n";
        std::cin>>input;
        if (input=='a'){
            //CIFRADO
            std::cout<<"\nCifrando...\n";
            //mensaje
            Cypher=testing.cypherwithsignature(message,eb,Nb);
            std::cout<<"\nMessage: \n"<<Cypher.at(0)<<"\nSignature: \n"<<Cypher.at(1);
        }
        else if (input=='b'){
            //DECIFRADO
            std::cout<<"\nDescifrando...\n";
            //mensaje
            DCypher.push_back(""); //Aqui se ingresa el mensaje cifrado.
            //firma
            DCypher.push_back(""); //Aqui se ingresa la firma cifrada.
            DCypher=testing.decypherwithsignature(DCypher,eb,Nb);
            std::cout<<"\nMensaje:\n"<<DCypher.at(0)<<"\nFirma:\n"<<DCypher.at(1);
        }
    }
}
