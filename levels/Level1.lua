Level1 =  {
	map = {
		textureAssetId = "terrain-texture-day",
		file = "levels/Level1.map",
		scale = 2,
		tileSize = 32,
		mapSizeX = 26,
		mapSizeY = 20,
	},

	entities = {
		[0] = {
			name = "player",
			layer = 4,
			components = {
				transform = {
					position = {
						x = 0,
						y = 0
					},
					velocity = {
						x = 0,
						y = 0
					},
					width = 32,
					height = 32,
					scale = 1,
					rotation = 0
				},
				sprite = {
					textureAssetId = "chopper-sinngle",
					animated = true,
					frameCount = 2,
					animationSpeed = 90,
					hasDirections = true,
					fixed = false
				},
				collider = {
					tag = "PLAYER"
				},
				input = {
					keyboard = {
						up = "w",
						left = "a",
						down = "s",
						right = "d",
						shoot = "space"
					}
				}
			}
		},
		[1] = {
			name = "tank",
			layer = 2,
			components = {
				transform = {
					position = {
						x = 0,
						y = 0
					},
					velocity = {
						x = 0,
						y = 0
					},
					width = 32,
					height = 32,
					scale = 1,
					rotation = 0
				},
				sprite = {
					textureAssetId = "tank-big",
					animated = false
				},
				collider = {
					tag = "ENEMY"
				}
			}
		},
		[2] = {
			name = "truck",
			layer = 3,
			components = {
				transform = {
					position = {
						x = 0,
						y = 0
					},
					velocity = {
						x = 0,
						y = 0
					},
					width = 32,
					height = 32,
					scale = 1,
					rotation = 0
				},
				sprite = {
					textureAssetId = "truck",
					animated = false
				},
				collider = {
					tag = "VEGETATION"
				}
			}
		}
	}
}
