/*
 *   Ce fichier fait partie d'un projet de programmation donné en Licence 3 
 *   à l'Université de Bordeaux
 *
 *   Copyright (C) 2015 Adrien Boussicault
 *
 *    This Library is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This Library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this Library.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "automate.h"
#include "outils.h"

void wrap_liberer_automate( Automate * aut ){
	if( aut ){
		liberer_automate(aut);
	}
}

int test_automate_union(){

	int result = 1;

	{
		Automate * aut1 = mot_to_automate("ab");
		Automate * aut2 = mot_to_automate("ba");

		Automate * mela = creer_union_des_automates( aut1, aut2 );
		
		TEST(
			1
			&& mela
			&& le_mot_est_reconnu( mela, "ab" )
			&& le_mot_est_reconnu( mela, "ba" )
			&& ! le_mot_est_reconnu( mela, "" )
			&& ! le_mot_est_reconnu( mela, "a" )
			&& ! le_mot_est_reconnu( mela, "b" )
			&& ! le_mot_est_reconnu( mela, "aa" )
			&& ! le_mot_est_reconnu( mela, "bb" )
			&& ! le_mot_est_reconnu( mela, "aaa" )
			&& ! le_mot_est_reconnu( mela, "aab" )
			&& ! le_mot_est_reconnu( mela, "aba" )
			&& ! le_mot_est_reconnu( mela, "abb" )
			&& ! le_mot_est_reconnu( mela, "baa" )
			&& ! le_mot_est_reconnu( mela, "bab" )
			&& ! le_mot_est_reconnu( mela, "bba" )
			&& ! le_mot_est_reconnu( mela, "bbb" )
			, result
		);
		wrap_liberer_automate( aut1 );
		wrap_liberer_automate( aut2 );
		wrap_liberer_automate( mela );
	}


	{
		Automate * aut1 = creer_automate();

		ajouter_transition( aut1, 0, 'a', 1 );
		ajouter_transition( aut1, 1, 'b', 2 );
		ajouter_transition( aut1, 2, 'a', 2 );
		ajouter_transition( aut1, 2, 'b', 1 );
		ajouter_etat_initial( aut1, 0 );
		ajouter_etat_final( aut1, 1 );
		

		Automate * aut2 = creer_automate();

		ajouter_transition( aut2, 0, 'c', 1 );
		ajouter_transition( aut2, 1, 'd', 1 );
		ajouter_transition( aut2, 0, 'd', 0 );
		ajouter_transition( aut2, 1, 'e', 0 );
		ajouter_etat_initial( aut2, 0 );
		ajouter_etat_final( aut2, 1 );

		Automate * mela = creer_union_des_automates( aut1, aut2 );

		TEST(
			1
			&& mela
			&&  le_mot_est_reconnu( mela, "a" )
			&&  le_mot_est_reconnu( mela, "c" )
			&& ! le_mot_est_reconnu( mela, "" )
			&& ! le_mot_est_reconnu( mela, "b" )
			&& ! le_mot_est_reconnu( mela, "d" )
			&& ! le_mot_est_reconnu( mela, "e" )

			&& le_mot_est_reconnu ( mela, "dc")
			&& le_mot_est_reconnu ( mela, "cec")
			&& le_mot_est_reconnu ( mela, "abb")
			&& !le_mot_est_reconnu( mela, "da")

			, result
		);
		wrap_liberer_automate( aut1 );
		wrap_liberer_automate( aut2 );
		wrap_liberer_automate( mela );
		}

	return result;
}


int main(){

    if( ! test_automate_union() ){ return 1; }

	return 0;
}
