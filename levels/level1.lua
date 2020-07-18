level1 =  {
	map = {
		textureAssetId = "terrain-texture-day",
		file = "levels/level1.map",
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
						x = -0.593746,
						y = 1.16666
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
			},
		},
		[1] = {
			name = "tank",
			layer = 2,
			components = {
				transform = {
					position = {
						x = -19.3438,
						y = 11.1667
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
			},
		}
	}
}
