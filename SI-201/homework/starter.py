# Name: Sinclair Hansen
# UMICH Uniqname: sihansen
# Collaborators:
# GenAI used and how? :
# Did your use of GenAI on this assignment align with your 
# goals and guidelines in your Gen AI contract? If not, why? :
import sqlite3
import matplotlib.pyplot as plt
import unittest
import os
import shutil
import re
import numpy as np


def clean_data(db) -> None:
    """
    Applies necessary cleaning to the tracks table in the database.
    
    Args:
        db (str): Path to the SQLite database file
    """
    conn = sqlite3.connect(db)
    cursor = conn.cursor()

    cursor.execute('''UPDATE tracks
                SET song_length = ROUND(song_length/60.0, 2)''')
                   
    cursor.execute('''DELETE FROM tracks
                WHERE album_id IS NULL
                   
                   ''')
    conn.commit()
    conn.close()


    



def find_top_artists(db):
    """
    Returns the top 5 most-played artists.
    
    Args:
        db (str): Path to the SQLite database file
    Returns:
        dict: Dictionary with artist names as keys and play counts as values
    """

    d_out = {}
    conn = sqlite3.connect(db)
    cursor = conn.cursor()
    cursor.execute("""
        SELECT artists.name, COUNT(*) AS play_count
        FROM user_history
        JOIN tracks ON user_history.track_id = tracks.id
        JOIN albums ON tracks.album_id = albums.id
        JOIN artists ON albums.artist_id = artists.id
        GROUP BY artists.id, artists.name
        ORDER BY play_count DESC
        LIMIT 5
    """)
    results = cursor.fetchall()
    for singer, counts in results:
        d_out[singer] = counts

    conn.commit()
    conn.close()

    return d_out

def plot_album_lengths(db, artist_name):
    """
    Args:
        db (str): Path to the SQLite database file
        song_dict (dict): Output from find_top_artists(db) function
    """
    conn = sqlite3.connect(db)
    cursor = conn.cursor()
    cursor.execute("""
    SELECT albums.name, ROUND(SUM(tracks.song_length), 2) AS total_length
    FROM albums
    JOIN artists ON albums.artist_id = artists.id
    JOIN tracks ON tracks.album_id = albums.id
    WHERE artists.name = ?
    GROUP BY albums.id, albums.name
    ORDER BY total_length DESC
    """, (artist_name,))

    results = cursor.fetchall()
    if not results:
        print("No artist found.")
        return
    albums = []
    length = []
    for row in results:
        albums.append(row[0])
        length.append(row[1])
    fig, ax = plt.subplots()
    bar = ax.bar(albums, length, color=['red', 'blue', 'green', 'orange'])
    ax.set_xlabel("Album")
    ax.set_ylabel("Total length (minutes)")
    ax.tick_params(axis='x', labelrotation=45, labelsize = 5)
    ax.bar_label(bar, padding=5)

    plt.title(artist_name + " - Album Lengths")
    plt.show()

    conn.close()




def top_artist_recap(db, song_dict) -> dict:
        """
        Args:
            db (str): Path to the SQLite database file
            song_dict (dict): Output from find_top_artists(db) function
        """
        pass

class TestSpotifyWrapped(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        # Path to the original and fixed databases
        cls.original_db = "listening_data.db"
        cls.fixed_db = "fixed_listening_data.db"

        if os.path.exists(cls.fixed_db):
            os.remove(cls.fixed_db)

        if os.path.exists('top_songs.png'):
            os.remove('top_songs.png')
        
        # Create a fixed version of the database for other tests
        shutil.copy2(cls.original_db, cls.fixed_db)
        clean_data(cls.fixed_db)

    def setUp(self):
        # Create fresh connections for each test
        self.original_conn = sqlite3.connect(self.original_db)
        self.fixed_conn = sqlite3.connect(self.fixed_db)
        self.original_cursor = self.original_conn.cursor()
        self.fixed_cursor = self.fixed_conn.cursor()

    def tearDown(self):
        # Close connections after each test
        self.original_conn.close()
        self.fixed_conn.close()


    def test_clean_data(self):
        #check initial state in original database
        self.fixed_cursor.execute("SELECT COUNT(*) FROM tracks WHERE song_length > 10")
        initial_count = self.fixed_cursor.fetchone()[0]
        self.assertEqual(initial_count, 0, "Should have no tracks with length > 10 after cleanup")
        
        self.original_cursor.execute("SELECT COUNT(*) FROM tracks WHERE album_id IS NULL")
        initial_null_count = self.original_cursor.fetchone()[0]
        self.original_cursor.execute("SELECT COUNT(*) FROM tracks")
        total_tracks = self.original_cursor.fetchone()[0]
        
        self.fixed_cursor.execute("SELECT COUNT(*) FROM tracks WHERE album_id IS NULL")
        final_null_count = self.fixed_cursor.fetchone()[0]
        self.fixed_cursor.execute("SELECT COUNT(*) FROM tracks")
        final_total_tracks = self.fixed_cursor.fetchone()[0]
        
        self.assertEqual(final_null_count, 0, "Should have no tracks with NULL album_id after cleanup")
        self.assertEqual(total_tracks-final_total_tracks, initial_null_count, "There should not be any other deletions besides NULL album_id tracks")

    def test_find_top_artists(self):
        top_artists = find_top_artists(self.fixed_db)
        
        # Verify expected top artists
        expected_artists = {
            'Bad Bunny': 196,
            'Lady Gaga': 222,
            'Tate McRae': 188,
            'FKA twigs': 160,
            'horsegiirL': 149
        }
        
        self.assertEqual(top_artists, expected_artists)
        
        # Check if values are in descending order
        plays = list(top_artists.values())
        self.assertEqual(plays, sorted(plays, reverse=True))

    def test_plot_album_lengths(self):
        """Test that album total length correctly sums its tracks"""
        result = plot_album_lengths(self.fixed_db,"Poppy")

        if result:
            # Verify at least one album returned
            self.assertIsNotNone(result)
            self.assertGreater(len(result), 0)

            first_album = list(result.keys())[0]
            # Query to verify
            self.fixed_cursor.execute("""
                SELECT SUM(t.song_length)
                FROM tracks t
                JOIN albums a ON t.album_id = a.id
                JOIN artists ar ON a.artist_id = ar.id
                WHERE ar.name = 'Poppy' AND a.name = ?
            """, (first_album,))
            
            manual_sum = self.fixed_cursor.fetchone()[0]
            self.assertAlmostEqual(result[first_album], manual_sum, places=2)

            """Test no duplicate albums appear in result"""
            self.assertEqual(len(result.keys()), len(set(result.keys())))

            """Test returned dictionary format is correct"""
            for album, length in result.items():
                self.assertIsInstance(album, str)
                self.assertIsInstance(length, float)
                self.assertGreater(length, 0)
        result = plot_album_lengths(self.fixed_db,"Shygirl")

    def test_top_artist_recap(self):
        top_artists = find_top_artists(self.fixed_db)
        top_artist_recap(self.fixed_db, top_artists)
        
        # Check if discovery.txt was created
        self.assertTrue(os.path.exists('discovery.txt'))
        
        # Verify contents of discovery.txt
        with open('discovery.txt', 'r') as f:
            content = f.readlines()
        
        check = lambda x: re.search(r'\d\)\s+([\w\s]+)\-\s+([\d\.]+)', x).group(1, 2)
        correct = lambda x: (x[0].strip(), x[1])
        
        self.assertEqual(len(content), 6)  # 1 header + 5 artists
        self.assertEqual(content[0].strip(), "Yearly Recap")
        self.assertEqual(correct(check(content[1])), ("Lady Gaga", "760.49"))
        self.assertEqual(correct(check(content[2])), ("Bad Bunny", "718.99"))
        self.assertEqual(correct(check(content[3])), ("horsegiirL", "647.02"))
        self.assertEqual(correct(check(content[4])), ("Tate McRae", "604.53"))
        self.assertEqual(correct(check(content[5])), ("FKA twigs", "488.7"))

if __name__ == '__main__':
    unittest.main(verbosity=2)